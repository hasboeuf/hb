// Qt
#include <QtCore/QFile>
#include <QtCore/QDebug>
#include <QtCore/QSettings>
#include <QtXml/QDomDocument>
// Hb
#include <HbLogService.h>
// Local
#include <LogViewerConfig.h>

using namespace hb::log;
using namespace hb::logviewer;


LogViewerConfig::LogViewerConfig() : 
    HbLogConfig()
{
    
}

LogViewerConfig::LogViewerConfig( const LogViewerConfig & config ) :
    HbLogConfig( config )
{
    if( &config != this )
    {
        mProjectFolders = config.mProjectFolders;
        mEditorDefault  = config.mEditorDefault;
        mEditorCommands = config.mEditorCommands;
    }
}


LogViewerConfig & LogViewerConfig::operator =( const LogViewerConfig & config )
{
    if( &config != this )
    {
        HbLogConfig::operator=( config );
        mProjectFolders = config.mProjectFolders;
        mEditorDefault  = config.mEditorDefault;
        mEditorCommands = config.mEditorCommands;
    }

    return ( *this );
}

void LogViewerConfig::buildDomFromConfig(QDomElement& root) const
{
    HbLogConfig::buildDomFromConfig( root );

    QDomDocument dom = root.ownerDocument();

    // Project dir
    QDomElement project_folders = dom.createElement( QStringLiteral( "projectFolders" ) );
    foreach( QString folder, mProjectFolders )
    {
        QDomElement project_folder = dom.createElement( QStringLiteral( "projectFolder" ) );
        project_folder.setAttribute( QStringLiteral( "path" ), folder );
        project_folders.appendChild( project_folder );
    }

    // Editors
    QDomElement editors = dom.createElement( QStringLiteral( "editors" ) );
    QMap<QString, QString>::const_iterator it_e = mEditorCommands.constBegin();
    while ( it_e != mEditorCommands.constEnd() )
    {
        QDomElement editor = dom.createElement( QStringLiteral( "editor" ) );

        QString editor_default = QString::number( ( mEditorDefault == it_e.key() ) ? 1 : 0 );

        editor.setAttribute( QStringLiteral( "name" ), it_e.key() );
        editor.setAttribute( QStringLiteral( "default" ), editor_default );
        editor.appendChild(dom.createTextNode( it_e.value() ) );

        editors.appendChild( editor );

        ++it_e;
    }

    root.appendChild( project_folders );
    root.appendChild( editors );
}

bool LogViewerConfig::exportConfigXml( const QString & file_path, const LogViewerConfig & config )
{
    QFile xml_doc( file_path );
    if( !xml_doc.open( QIODevice::WriteOnly ) )
    {
        qDebug() << "Erreur à l'écriture du document XML : " << xml_doc.errorString();
        return false;
    }

    QDomDocument dom( QStringLiteral( "hbLogViewerConfig" ) );
    QDomElement root = dom.createElement( QStringLiteral( "hbLogViewerConfig" ) );
    dom.appendChild( root );

    config.buildDomFromConfig( root );

    QTextStream ts( &xml_doc );
    ts << dom.toString();

    xml_doc.close();

    return true;
}

void LogViewerConfig::buildConfigFromDom( QDomElement & root )
{
    HbLogConfig::buildConfigFromDom( root );

    QDomNode node = root.firstChild();

    while ( !node.isNull() )
    {
        QString tag = node.nodeName();

        if( tag == QLatin1String( "projectFolders" ) )
        {
            QDomNodeList project_folders_children = node.childNodes();

            for( qint32 i = 0; i < project_folders_children.size(); ++i )
            {
                QString child_tag = project_folders_children.at( i ).toElement().tagName();
                if( child_tag == QLatin1String( "projectFolder" ) )
                {
                    QDomNode project_folder = project_folders_children.at( i );

                    QString project_folder_path = project_folder.toElement().attribute( QStringLiteral( "path" ) );
                    mProjectFolders.append( project_folder_path );
                }
            }
        }
        else if (tag == QLatin1String( "editors" ) )
        {
            QDomNodeList editors_children = node.childNodes();

            for( qint32 i = 0; i < editors_children.size(); ++i )
            {
                QString child_tag = editors_children.at( i ).toElement().tagName();
                if ( child_tag == QLatin1String( "editor" ) )
                {
                    QDomNode editor = editors_children.at( i );

                    QString editor_name = editor.toElement().attribute( QStringLiteral( "name" ) );
                    qint32 editor_default = editor.toElement().attribute( QStringLiteral( "default" ) ).toInt();

                    if( editor_default == 1 )
                    {
                        mEditorDefault = editor_name;
                    }

                    mEditorCommands.insert( editor_name, editor.toElement().text() );
                }
                else
                {
                    // qDebug() << QStringLiteral("Unknown tag: logger > editors > ") + tag;
                }
            }
        }
        else
        {
            //qDebug() << QStringLiteral("Unknown tag: logger > ") + tag;
        }

        node = node.nextSibling();
    }
}

const LogViewerConfig LogViewerConfig::importConfigXml( const QString & file_path )
{
    LogViewerConfig config;

    QFile xml_doc( file_path );
    if( !xml_doc.open( QIODevice::ReadOnly ) )
    {
        qDebug() << QStringLiteral( "Erreur %1[%2] à l'ouverture du document XML %3" )
            .arg( xml_doc.error() )
            .arg( xml_doc.errorString() )
            .arg( xml_doc.fileName() );

        return config;
    }

    QDomDocument * dom = q_check_ptr( new QDomDocument( QStringLiteral( "hbLogViewerConfig" ) ) );

    if( !dom->setContent( &xml_doc ) )
    {
         xml_doc.close();
         qDebug() << "Erreur à l'ouverture du document XML";
         return config;
    }

    xml_doc.close();

    QDomElement root = dom->documentElement();
    QDomNode node = root.firstChild();

    config.buildConfigFromDom(root);

    return config;
}

void LogViewerConfig::loadSettings()
{
    QSettings settings;

    if( settings.childGroups().isEmpty() ) // First start, we load the default XML config file.
    {
        this->operator=( LogViewerConfig::importConfigXml( QString::fromLatin1( LogViewerConfig::msDefaultConfigXml ) ) );
        saveSettings();
        return;
    }

    HbLogConfig::loadSettings();

    // Project folders
    mProjectFolders.clear();
    mProjectFolders = settings.value( QStringLiteral( "general/paths" ) ).toStringList();

    // Editors
    mEditorDefault = settings.value( QStringLiteral( "editors/default" ) ).toString();

    mEditorCommands.clear();
    settings.beginGroup( QStringLiteral( "editors/commands" ) );
    QStringList editors = settings.childKeys();
    foreach (const QString editor, editors)
    {
        mEditorCommands[editor] = settings.value( editor ).toString();
    }
    settings.endGroup();

}

void LogViewerConfig::saveSettings()
{
    HbLogConfig::saveSettings();

    QSettings settings;

    // Project folders
    settings.setValue( QStringLiteral( "general/paths" ), mProjectFolders );

    // Editors
    settings.setValue( QStringLiteral( "editors/default" ), mEditorDefault );

    QMap<QString, QString>::const_iterator icommands = mEditorCommands.constBegin();
    settings.beginGroup( QStringLiteral( "editors/commands" ) );
    settings.remove( QString() ); // All keys in the current group() are removed.
    while(icommands != mEditorCommands.constEnd())
    {
        settings.setValue( icommands.key(), icommands.value() );
        ++icommands;
    }
    settings.endGroup();

    settings.sync(); // Commit.
}

void LogViewerConfig::addEditor( const QString & name, const QString & path )
{
    mEditorCommands.insert( name, path );
}

const QString LogViewerConfig::editorCommand( const QString & editor_name ) const
{
    if( mEditorCommands.contains( editor_name ))
    {
        return mEditorCommands.value( editor_name );
    }

    return QString();
}

void LogViewerConfig::resetEditors()
{
    return mEditorCommands.clear();
}

QMap< QString, QString > LogViewerConfig::editors() const
{
    return mEditorCommands;
}

QString LogViewerConfig::defaultEditor() const
{
    return mEditorDefault;
}

void LogViewerConfig::setDefaultEditor( const QString & editor)
{
    mEditorDefault = editor;
}

void LogViewerConfig::resetProjectFolders()
{
    mProjectFolders.clear();
}

QStringList LogViewerConfig::projectFolders() const
{
    return mProjectFolders;
}

void LogViewerConfig::addProjectFolder( const QString & folder )
{
    mProjectFolders.append( folder );
}
