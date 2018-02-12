// Qt
#include <QtCore/QDebug>
// Hb
#include <HbLogService.h>
// Local
#include <HbPluginPlatform.h>
#include <IHbPlugin.h>
#include <HbPluginInfos.h>
#include <HbPluginService.h>

using namespace hb::plugin;

HbPluginPlatform::HbPluginPlatform() :
    QObject(), mPluginManager( this )
{

    connect( &mPluginManager, &HbPluginManager::pluginStateChanged,
             this,            &HbPluginPlatform::onPluginStateChanged, Qt::UniqueConnection );
}

void HbPluginPlatform::loadPlugins  ( const QString & plugin_folder )
{
    mPluginManager.load( plugin_folder );
}

void HbPluginPlatform::unloadPlugins()
{
    mPluginManager.unload();
}

QList< HbPluginInfos > HbPluginPlatform::pluginInfoList()
{
    return mPluginManager.pluginInfoList();
}

HbPluginService * HbPluginPlatform::requestService( const QString & service_name ) const
{
    if( mServices.contains( service_name ) && mServices.value( service_name ) )
    {
        return mServices.value( service_name );
    }

    return nullptr;
}

void HbPluginPlatform::registerService( HbPluginService * service )
{
    if( !service )
    {
        return;
    }

    QString name = service->name();

    if( mServices.contains( name ) )
    {
        return;
    }

    mServices.insert( name, service );
}

const IHbPlugin *HbPluginPlatform::requestPlugin( const QString & name )   const
{
    return mPluginManager.plugin( name );
}

QString HbPluginPlatform::isServiceRegistered( const QString & service_name ) const
{
    if(mServices.contains( service_name ) && mServices.value( service_name ) )
    {
        return mServices.value( service_name )->version();
    }

    return QString();
}

void HbPluginPlatform::onPluginStateChanged( const HbPluginInfos & plugin_infos )
{
    emit pluginStateChanged( plugin_infos );
}

void HbPluginPlatform::onLoadPluginRequest  ( const QString & plugin_name )
{
    HbInfo( "Load request (plugin=%s).", HbLatin1( plugin_name ) );
    mPluginManager.loadPluginFromName( plugin_name );
}

void HbPluginPlatform::onUnloadPluginRequest( const QString & plugin_name )
{
    HbInfo( "Unload request (plugin=%s).", HbLatin1( plugin_name ) );
    mPluginManager.unloadPlugin( plugin_name );
}
