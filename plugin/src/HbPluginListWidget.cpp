// Qt
#include <QtCore/QDebug>
// Hb
#include <HbPluginListWidget.h>
#include <HbLogService.h>

using namespace hb::plugin;

HbPluginListWidget::HbPluginListWidget( QWidget * parent ) :
    QWidget( parent )
{
    setupUi( this );

    mLabels.insert( COLUMN_NAME,     QStringLiteral( "Name"     ) );
    mLabels.insert( COLUMN_LOAD,     QStringLiteral( "Loaded"   ) );
    mLabels.insert( COLUMN_VERSION,  QStringLiteral( "Version"  ) );
    mLabels.insert( COLUMN_AUTHOR,   QStringLiteral( "Author"   ) );
    mLabels.insert( COLUMN_REQUIRED, QStringLiteral( "Required" ) );
    mLabels.insert( COLUMN_OPTIONAL, QStringLiteral( "Optional" ) );

    mModel.setHorizontalHeaderLabels( mLabels );
    mProxy.setSourceModel( &mModel );

    connect( &mModel, &QStandardItemModel::itemChanged,
             this, &HbPluginListWidget::onPluginChecked, Qt::UniqueConnection );

    qtv_plugins->setModel( &mProxy );
    qtv_plugins->setAlternatingRowColors( true );
    qtv_plugins->setSelectionBehavior( QAbstractItemView::SelectRows );
    qtv_plugins->setSelectionMode( QAbstractItemView::SingleSelection );
    qtv_plugins->verticalHeader()->hide();
    qtv_plugins->setEditTriggers( QAbstractItemView::NoEditTriggers );
    qtv_plugins->verticalHeader()->setDefaultSectionSize( 20 );
    qtv_plugins->setSortingEnabled( true );
}

QStandardItem * HbPluginListWidget::getLoadItem( const QString & plugin_name )
{
    QStandardItem * item_name = mPlugins.value( plugin_name );
    if( !item_name )
    {
        return nullptr;
    }

    int row = item_name->row();

    return mModel.item( row, COLUMN_LOAD );
}


void HbPluginListWidget::onPluginStateChanged( const HbPluginInfos & plugin_infos )
{
    HbInfo( "onPluginStateChanged state=%s", HbLatin1( plugin_infos.stateStr() ) );

    // Unregistered plugin.
    if( plugin_infos.state() == HbPluginInfos::PLUGIN_NOT_REGISTERED )
    {
        QStandardItem * item_load = getLoadItem( plugin_infos.name() );
        if( item_load )
        {
            mModel.removeRow( item_load->row() );
        }
        mPlugins.remove( plugin_infos.name() );

        return;
    }

    if( !mPlugins.contains( plugin_infos.name() ) ) // Plugin not exists.
    {
        QStandardItem * item_name     = new QStandardItem();
        QStandardItem * item_load     = new QStandardItem();
        QStandardItem * item_version  = new QStandardItem();
        QStandardItem * item_author   = new QStandardItem();
        QStandardItem * item_required = new QStandardItem();
        QStandardItem * item_optional = new QStandardItem();

        item_load->setFlags( item_load->flags() | Qt::ItemIsUserCheckable );

        item_name->setData        ( plugin_infos.name(),            Qt::DisplayRole );
        item_load->setData        ( Qt::Unchecked,                  Qt::CheckStateRole ); // Initial state.
        item_load->setData        ( Qt::Unchecked,                  ROLE_PLUGIN_CHECKSTATE ); // Store previous checkstate to do a proper action.
        item_load->setData        ( plugin_infos.name( ),           ROLE_PLUGIN_NAME ); // To retrieve efficiently the name of the plugin when the checkbox is un/checked.
        item_version->setData     ( plugin_infos.version(),         Qt::DisplayRole );
        item_author->setData      ( plugin_infos.author(),          Qt::DisplayRole );
        item_required->setData    ( plugin_infos.requiredPluginsStr() + " " +
                                    plugin_infos.requiredServicesStr(), Qt::DisplayRole );
        item_optional->setData    ( plugin_infos.optionalPluginsStr() + " " +
                                    plugin_infos.optionalServicesStr(), Qt::DisplayRole );

        QList< QStandardItem * > plugin_row;
        plugin_row.append( item_name     );
        plugin_row.append( item_load     );
        plugin_row.append( item_version  );
        plugin_row.append( item_author   );
        plugin_row.append( item_required );
        plugin_row.append( item_optional );

        mPlugins.insert( plugin_infos.name(), item_name );

        mModel.appendRow( plugin_row );
    }

    // Update checkbox.
    QStandardItem * item_load = getLoadItem( plugin_infos.name() );
    if( item_load )
    {
        disconnect( &mModel, &QStandardItemModel::itemChanged, this, &HbPluginListWidget::onPluginChecked ); // Avoid to call onPluginChecked.

        // TODO use PLUGIN_CHANGING?

        // Change state
        if( plugin_infos.state() == HbPluginInfos::PLUGIN_LOADED )
        {
            item_load->setData( Qt::Checked, Qt::CheckStateRole);
        }
        else if( plugin_infos.state() == HbPluginInfos::PLUGIN_LOADED_PARTIALLY )
        {
            item_load->setData( Qt::PartiallyChecked, Qt::CheckStateRole);
        }
        else
        {
            item_load->setData( Qt::Unchecked, Qt::CheckStateRole);
        }
        item_load->setData( item_load->data( Qt::CheckStateRole ), ROLE_PLUGIN_CHECKSTATE ); // Store previous state.

        connect( &mModel, &QStandardItemModel::itemChanged, this, &HbPluginListWidget::onPluginChecked, Qt::UniqueConnection );
    }
}

void HbPluginListWidget::onPluginChecked( QStandardItem * item_load )
{
    if( !item_load )
    {
        return;
    }

    QString plugin_name = item_load->data( ROLE_PLUGIN_NAME ).toString();

    disconnect( &mModel, &QStandardItemModel::itemChanged, this, &HbPluginListWidget::onPluginChecked ); // Avoid to call onPluginChecked.

    qint32 previous_state = item_load->data( ROLE_PLUGIN_CHECKSTATE ).toInt( );
    if( previous_state == Qt::Unchecked )
    {
        emit loadPluginRequest( plugin_name );
    }
    else
    {
        emit unloadPluginRequest( plugin_name );
    }

    connect( &mModel, &QStandardItemModel::itemChanged, this, &HbPluginListWidget::onPluginChecked, Qt::UniqueConnection );
}
