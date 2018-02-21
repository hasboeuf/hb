// Qt
#include <QtCore/QDebug>
#include <QtCore/QProcess>
#include <QtCore/QDir>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QTime>
#include <QtGui/QClipboard>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QMenu>
// Hb
#include <HbLogService.h>
#include <HbLogMessage.h>
#include <gui/HbLogConfig.h>
#include <outputs/HbLogFileOutput.h>
// Local
#include <LogViewerTab.h>
#include <LogViewerTabDelegate.h>
#include <LogViewerConfig.h>

using namespace hb::logviewer;
using namespace hb::log;

LogViewerTab::LogViewerTab( qint32 id,
                            const LogViewerConfig & config,
                            bool rerun,
                            ModelFilter * filter,
                            ColumnId filter_column,
                            QWidget * parent ) :
    QWidget( parent ), mConfig( config )
{
    setupUi(this);

    mId           = id;
    mpFilter      = filter;
    mFilterColumn = filter_column;
    mFrozen       = rerun;
    mRerun        = rerun;

    if( rerun )
    {
        qpb_freeze->setEnabled( false );
    }

    mpFreezeAnimation = q_check_ptr ( new QPropertyAnimation( this, "_freezeAnimationValue" ) );
    mpFreezeAnimation->setDuration  ( 2000 );
    mpFreezeAnimation->setLoopCount ( -1 );
    mpFreezeAnimation->setStartValue( 0.f );
    mpFreezeAnimation->setKeyValueAt( 0.5, 1.f );
    mpFreezeAnimation->setEndValue  ( 0.f );

    mFreezeAnimationValue = -1.f;

    for( const QString level: HbLogger::MetaLevel::toString() )
    {
        if( !level.contains( QLatin1String( "_ALL" ) ) && !level.contains( QLatin1String( "_NONE" ) ) )
        {
            HbLogger::Level enum_level = HbLogger::MetaLevel::fromString(level);

            qcb_level->addItem( level, enum_level );
        }
    }

    updateView(); // Update icon colors. At this time, the config is not loaded so black icons will be drawn.

    mLabels.insert( COLUMN_LEVEL, QStringLiteral( "Level"   ) );
    mLabels.insert( COLUMN_TIME,  QStringLiteral( "Time"    ) );
    mLabels.insert( COLUMN_OWNER, QStringLiteral( "Owner"   ) );
    mLabels.insert( COLUMN_LINE,  QStringLiteral( "Line"    ) );
    mLabels.insert( COLUMN_WHERE, QStringLiteral( "Where"   ) );
    mLabels.insert( COLUMN_TEXT,  QStringLiteral( "Message" ) );
    mLabels.insert( COLUMN_FILE,  QStringLiteral( "File"    ) );
    mLabels.insert( COLUMN_FUNC,  QStringLiteral( "Func"    ) );

    mProxy.setSourceModel( &mModel );

    qtv_log->setModel( &mProxy );
    qtv_log->setAlternatingRowColors( true );
    qtv_log->setSelectionBehavior( QAbstractItemView::SelectRows );
    qtv_log->setSelectionMode( QAbstractItemView::SingleSelection );
    qtv_log->verticalHeader()->hide();
    qtv_log->setEditTriggers( QAbstractItemView::NoEditTriggers );
    qtv_log->verticalHeader()->setDefaultSectionSize( 20 );
    qtv_log->setSortingEnabled( true );
    qtv_log->setShowGrid( false );
    qtv_log->setContextMenuPolicy( Qt::CustomContextMenu );
    qtv_log->setItemDelegate( q_check_ptr( new LogViewerTabDelegate( qtv_log ) ) );

    initTable();

    connect( qcb_level,          ( void ( QComboBox::* )( int ) ) &QComboBox::currentIndexChanged,
             this,               &LogViewerTab::onLevelChanged );
    connect( qle_filter_text,    &QLineEdit::textEdited,       this, &LogViewerTab::onFilterTextChanged );
    connect( qpb_clear,          &QPushButton::clicked,        this, &LogViewerTab::onClearClicked );
    connect( qpb_adjust_content, &QPushButton::clicked,        this, &LogViewerTab::onAdjustToContent );
    connect( qpb_save_as,        &QPushButton::clicked,        this, &LogViewerTab::onSaveAsClicked );
    connect( qpb_freeze,         &QPushButton::clicked,        this, &LogViewerTab::onFreezeClicked );
    connect( qtv_log,            &QTableView::doubleClicked,   this, &LogViewerTab::onRowDoubleClicked );
    connect( qtv_log,            &QTableView::customContextMenuRequested,
             this,               &LogViewerTab::onCustomContextMenuRequested);
}

LogViewerTab::~LogViewerTab()
{
    delete mpFilter;
}

qint32 LogViewerTab::id() const
{
    return mId;
}

void LogViewerTab::initTable()
{
    mModel.clear();
    mModel.setHorizontalHeaderLabels( mLabels );
    qtv_log->hideColumn( COLUMN_FILE );
    qtv_log->hideColumn( COLUMN_FUNC );
    qtv_log->horizontalHeader()->setStretchLastSection( true );

    mProxy.beginDeclareFilter();
    mProxy.removeFilters();
    mProxy.endDeclareFilter();
    mProxy.sort( COLUMN_TIME, Qt::AscendingOrder );

    checkMaxBuffer();
}

qreal LogViewerTab::freezeAnimationValue() const
{
    return mFreezeAnimationValue;
}

void  LogViewerTab::setFreezeAnimationValue( qreal value )
{
    mFreezeAnimationValue = value;

    if( value == -1.f )
    {
        QString style;
        style += QLatin1String( "QTableView  {\n" );
        style += QLatin1String( "border: none;\n" );
        style += QLatin1String( "}" );

        qtv_log->setStyleSheet( style );
    }
    else
    {
        QString style;
        style += QLatin1String( "QTableView  {\n" );
        style += QStringLiteral( "border: 3px solid rgba(255, 0, 0, %1);\n" ).arg( qRound( value * 255 ) );
        style += QLatin1String( "border-radius: 2px;\n" );
        style += QLatin1String( "}" );

        qtv_log->setStyleSheet( style );
    }
}

bool LogViewerTab::isValidEntry( QList< QStandardItem * > & row )
{

    if( !row.at( COLUMN_LEVEL ) ||
        !row.at( COLUMN_TIME  ) ||
        !row.at( COLUMN_OWNER ) ||
        !row.at( COLUMN_LINE  ) ||
        !row.at( COLUMN_WHERE ) ||
        !row.at( COLUMN_TEXT  ) ||
        !row.at( COLUMN_FILE  ) ||
        !row.at( COLUMN_FUNC  ) )
    {
        qDebug() << "Unexpected null pointer.";
        return false;
    }

    if( !mpFilter )
    {
        return true;
    }

    QStandardItem * item_to_be_filtered = row.at( mFilterColumn );
    return mpFilter->acceptsValue( item_to_be_filtered->data( mpFilter->mRole ) );
}

void LogViewerTab::addEntry( const HbLogMessage * msg, bool rerun )
{
    if( !msg )
    {
        return;
    }

    if( mFrozen && !rerun )
    {
        return;
    }

    QStandardItem * item_level = q_check_ptr( new QStandardItem() );
    QStandardItem * item_time  = q_check_ptr( new QStandardItem() );
    QStandardItem * item_owner = q_check_ptr( new QStandardItem() );
    QStandardItem * item_where = q_check_ptr( new QStandardItem() );
    QStandardItem * item_text  = q_check_ptr( new QStandardItem() );
    QStandardItem * item_line  = q_check_ptr( new QStandardItem() );
    QStandardItem * item_file  = q_check_ptr( new QStandardItem() );
    QStandardItem * item_func  = q_check_ptr( new QStandardItem() );


    QString line = QString::number( msg->context().line() );
    if( line == QLatin1String( "-1" ) ) line.clear();

    QString where = QStringLiteral( "%1::%2" )
                    .arg( msg->context().file() )
                    .arg( msg->context().function() );

    if( where == QLatin1String( "::" ) ) where.clear();

    item_level->setData( msg->levelStr(),           Qt::DisplayRole );
    item_level->setData( msg->level(),              Qt::UserRole    );
    item_time->setData ( msg->timestampStr(),       Qt::DisplayRole );
    item_time->setData ( msg->timestamp(),          Qt::UserRole    );
    item_owner->setData( msg->context().owner(),    Qt::DisplayRole );
    item_where->setData( where,                     Qt::DisplayRole );
    item_text->setData ( msg->message(),            Qt::DisplayRole );
    item_line->setData ( line,                      Qt::DisplayRole );
    item_file->setData ( msg->context().file(),     Qt::DisplayRole );
    item_func->setData ( msg->context().function(), Qt::DisplayRole );

    QBrush foreground_color;
    foreground_color.setColor(mConfig.colorByIdLevel( msg->level() ) );
    item_level->setData( foreground_color, Qt::ForegroundRole );
    item_time->setData ( foreground_color, Qt::ForegroundRole );
    item_owner->setData( foreground_color, Qt::ForegroundRole );
    item_line->setData ( foreground_color, Qt::ForegroundRole );
    item_where->setData( foreground_color, Qt::ForegroundRole );
    item_text->setData ( foreground_color, Qt::ForegroundRole );

    QList< QStandardItem * > row;
    row.insert( COLUMN_LEVEL, item_level );
    row.insert( COLUMN_TIME,  item_time  );
    row.insert( COLUMN_OWNER, item_owner );
    row.insert( COLUMN_LINE,  item_line  );
    row.insert( COLUMN_WHERE, item_where );
    row.insert( COLUMN_TEXT,  item_text  );
    row.insert( COLUMN_FILE,  item_file  );
    row.insert( COLUMN_FUNC,  item_func  );

    if( isValidEntry( row ) )
    {
        mModel.appendRow( row );
        checkMaxBuffer();
    }
    else
    {
        delete item_level;
        delete item_time;
        delete item_owner;
        delete item_where;
        delete item_text;
        delete item_line;
        delete item_file;
        delete item_func;
    }
}

void LogViewerTab::updateView()
{
    for( qint32 index = 0; index < qcb_level->count(); ++index )
    {
        QColor color = mConfig.colorByIdLevel( qcb_level->itemData(index).toInt() );
        QPixmap pix( 10, 10 );
        pix.fill( color );
        qcb_level->setItemIcon( index, QIcon( pix ) );
    }

    checkMaxBuffer();

    // Update the items color.
    for( qint32 row = 0; row < mModel.rowCount(); ++row )
    {

        QStandardItem* item_level = mModel.item( row, COLUMN_LEVEL );
        QStandardItem* item_time  = mModel.item( row, COLUMN_TIME  );
        QStandardItem* item_owner = mModel.item( row, COLUMN_OWNER );
        QStandardItem* item_line  = mModel.item( row, COLUMN_LINE  );
        QStandardItem* item_where = mModel.item( row, COLUMN_WHERE );
        QStandardItem* item_text  = mModel.item( row, COLUMN_TEXT  );

        if( !item_level || !item_time || !item_owner || !item_line || !item_where || !item_text )
        {
            qDebug() << "Unexpected null pointer.";
            continue;
        }

        QBrush foreground_color;
        foreground_color.setColor( mConfig.colorByIdLevel( item_level->data( Qt::UserRole ).toInt() ) );

        item_level->setData( foreground_color, Qt::ForegroundRole );
        item_time->setData ( foreground_color, Qt::ForegroundRole );
        item_owner->setData( foreground_color, Qt::ForegroundRole );
        item_line->setData ( foreground_color, Qt::ForegroundRole );
        item_where->setData( foreground_color, Qt::ForegroundRole );
        item_text->setData ( foreground_color, Qt::ForegroundRole );
    }
}

void LogViewerTab::checkMaxBuffer()
{
    qint32 max_buffer     = mConfig.maxBuffer();
    qint32 current_buffer = mModel.rowCount();

    qreal percent = ( current_buffer * 100.0 ) / ( qreal ) max_buffer;

    while( current_buffer > max_buffer )
    {
        mModel.removeRow( 0 );
        --current_buffer;
    }

    qpb_buffer->setValue( percent );
}

void LogViewerTab::onLevelChanged( int index )
{
    qint32 min_level = qcb_level->itemData( index ).toInt();

    QString regexp;
    regexp += QLatin1Char( '(' );

    qint32 current_level = HbLogConfig::msMaxLevel;
    while( current_level >= min_level )
    {
        regexp += QStringLiteral( "%1|").arg( current_level );
        current_level >>= 1;
    }

    regexp.chop( 1 ); // Remove the the last '|'.
    regexp += QLatin1Char( ')' );

    mProxy.beginDeclareFilter();
    mProxy.removeFilter( COLUMN_LEVEL);
    mProxy.setFilter( COLUMN_LEVEL, regexp, Qt::UserRole, Qt::MatchRegExp );
    mProxy.endDeclareFilter();

}

void LogViewerTab::onFilterTextChanged( const QString & filter )
{

    mProxy.removeFilter( COLUMN_TEXT );
    mProxy.beginDeclareFilter();
    mProxy.setFilter( COLUMN_TEXT, filter, Qt::DisplayRole, Qt::MatchContains );
    mProxy.endDeclareFilter();
}

void LogViewerTab::onClearClicked()
{
    initTable();
}

void LogViewerTab::onFreezeClicked( bool checked )
{
    mFrozen = checked;

    if( mpFreezeAnimation )
    {
        if( mFrozen )
        {
            mpFreezeAnimation->start();
        }
        else
        {
            mpFreezeAnimation->stop();
            setFreezeAnimationValue( -1.f );
        }
    }
}

void LogViewerTab::onAdjustToContent()
{
    qtv_log->resizeColumnToContents( COLUMN_TEXT );
}

void LogViewerTab::onSaveAsClicked()
{
    if( !mFrozen )
    {

        auto answer = QMessageBox::question(
                      this,
                      QStringLiteral( "Save as" ),
                      QStringLiteral( "During the saving process, freeze must be enabled. Alright?" ),
                      QMessageBox::Yes | QMessageBox::No );

        if( answer == QMessageBox::No )
        {
            return;
        }

        qpb_freeze->setChecked( true );
    }

    QString file_path = QFileDialog::getSaveFileName( this, QStringLiteral( "Save log" ), QString(), QString() );

    QFile file( file_path );
    if( !file.open( QIODevice::WriteOnly | QIODevice::Text ) )
    {
        return;
    }

    QString buffer;

    for( qint32 row = 0; row < mModel.rowCount(); ++row )
    {

        QStandardItem * item_level = mModel.item( row, COLUMN_LEVEL );
        QStandardItem * item_time  = mModel.item( row, COLUMN_TIME  );
        QStandardItem * item_owner = mModel.item( row, COLUMN_OWNER );
        QStandardItem * item_text  = mModel.item( row, COLUMN_TEXT  );
        QStandardItem * item_line  = mModel.item( row, COLUMN_LINE  );
        QStandardItem * item_file  = mModel.item( row, COLUMN_FILE  );
        QStandardItem * item_func  = mModel.item( row, COLUMN_FUNC  );

        if( !item_level || !item_time || !item_owner || !item_text || !item_line || !item_file || !item_func )
        {
            qDebug() << "Unexpected null pointer.";
            continue;
        }

        qint16  level = ( qint16 ) item_level->data( Qt::UserRole ).toInt();
        qint64  time  = ( qint64 ) item_time->data( Qt::UserRole ).toLongLong();
        QString owner = item_owner->data( Qt::DisplayRole ).toString();
        QString text  = item_text->data( Qt::DisplayRole ).toString();
        qint32  line  = ( qint32 ) item_line->data( Qt::DisplayRole ).toInt();
        QString file  = item_file->data( Qt::DisplayRole ).toString();
        QString func  = item_func->data( Qt::DisplayRole ).toString();

        HbLogContext context( owner, file.toStdString().c_str(), line, func.toStdString().c_str() );
        HbLogMessage msg( ( HbLogger::Level ) level, HbLogger::OUTPUT_ALL, context, time, text );

        buffer += HbLogMessage::toRaw( msg );
        buffer += QChar::LineFeed;
    }

    QByteArray ba = buffer.toUtf8();
    const char * data = ba.data();

    file.write( data );
    file.close();
}

void LogViewerTab::onRowDoubleClicked( const QModelIndex & index )
{
    QModelIndex index_source = mProxy.mapToSource( index );

    QStandardItem * item_line = mModel.item( index_source.row(), COLUMN_LINE );
    QStandardItem * item_file = mModel.item( index_source.row(), COLUMN_FILE );

    qint32  line = item_line->data( Qt::DisplayRole ).toInt();
    QString file = item_file->data( Qt::DisplayRole ).toString();

    QFileInfo file_info( file );
    file = file_info.fileName();

    QStringList   folders = mConfig.projectFolders();
    QSet< QString > found_paths;

    for( const QString folder: folders )
    {
        found_paths.unite(findAbsoluteFilePath( file, folder ) );
    }

    if( found_paths.isEmpty() )
    {
        qDebug() << QStringLiteral( "No path found for %1 : %2." ).arg( file ).arg( line );
        return;
    }

    QString file_to_open = *found_paths.begin();

    if( found_paths.size() > 1 )
    {
        QInputDialog dialog( this );
        dialog.setWindowTitle  ( QStringLiteral( "The file you want to open" ) );
        dialog.setTextValue    ( QStringLiteral( "File:" ) );
        dialog.setComboBoxItems( found_paths.values() );

        if( dialog.exec() == QDialog::Accepted )
        {
            file_to_open = dialog.textValue();
        }
        else
        {
            return;
        }
    }

    if( file_to_open.isEmpty() )
    {
        return;
    }

    QString cmd = mConfig.editorCommand( mConfig.defaultEditor() );
    if( cmd.isEmpty() )
    {
        qDebug() << "No command found.";
        return;
    }

    cmd.replace( QLatin1String( "$(FILE)" ), file_to_open );
    cmd.replace( QLatin1String( "$(LINE)" ), QString::number( line ) );

#ifndef QT_NO_PROCESS // Windows Phone.
    if( !QProcess::startDetached( cmd ) )
    {
        QMessageBox::critical( this,
                               QStringLiteral( "Error" ),
                               QStringLiteral( "Error while opening file." ),
                               QMessageBox::Ok );
    }
#endif
}

void LogViewerTab::onCustomContextMenuRequested( const QPoint & pos )
{
    QModelIndex index = qtv_log->indexAt( pos );
    if( !index.isValid() )
    {
        return;
    }

    QMenu * menu = q_check_ptr( new QMenu() );

    QAction * qa_new_tab           = menu->addAction( QStringLiteral( "Open in a new tab" ) );
    QAction * qa_copy_cell_content = menu->addAction( QStringLiteral( "Copy cell content" ) );

    connect( qa_new_tab,           &QAction::triggered, this, &LogViewerTab::onOpenNewTab );
    connect( qa_copy_cell_content, &QAction::triggered, this, &LogViewerTab::onCopyCellContent );

    menu->exec( qtv_log->mapToGlobal( pos ) );
}

void LogViewerTab::onOpenNewTab()
{
    QModelIndex index = qtv_log->currentIndex();
    if( !index.isValid() )
    {
        return;
    }

    QModelIndex index_right = mProxy.mapToSource( index );

    QStandardItem * selected_item = mModel.item( index_right.row(), index_right.column() );
    if( !selected_item )
    {
        return;
    }

    QString content = selected_item->data( Qt::DisplayRole ).toString();
    emit newTabRequest( index_right.column(), content );

}

void LogViewerTab::onCopyCellContent()
{
    QModelIndex index = qtv_log->currentIndex();
    if( !index.isValid() )
    {
        return;
    }

    QModelIndex index_right = mProxy.mapToSource( index );

    QStandardItem * selected_item = mModel.item( index_right.row(), index_right.column() );
    if( !selected_item )
    {
        return;
    }

    QString content = selected_item->data( Qt::DisplayRole ).toString();

    QClipboard * clipboard = QApplication::clipboard();
    clipboard->setText( content );
}

QSet< QString > LogViewerTab::findAbsoluteFilePath( const QString & file_path, const QString & root_path )
{
    QSet< QString > file_path_found;

    QFileInfo root_path_info( QStringLiteral( "%1/" ).arg( root_path ) );
    if( !root_path_info.exists() || !root_path_info.isDir() )
    {
        return file_path_found;
    }

    QDir root_path_dir  = root_path_info.dir();
    QStringList subdirs = root_path_dir.entryList( QDir::Dirs | QDir::NoDot | QDir::NoDotDot );

    // Browse subdirs
    for( const QString subdir: subdirs )
    {
        QString subdir_path = QStringLiteral( "%1%2/" )
            .arg( root_path_info.absoluteFilePath() ).arg( subdir );

        file_path_found.unite( findAbsoluteFilePath( file_path, subdir_path ) );
    }

    // Check current dir
    QString full_file_path = QStringLiteral( "%1/%2" )
                             .arg( root_path )
                             .arg( file_path );

    QFileInfo file_info( full_file_path );
    if( file_info.exists() && file_info.isFile() )
    {
        full_file_path = QDir::cleanPath( full_file_path );

        file_path_found.insert( full_file_path );
    }

    return file_path_found;
}
