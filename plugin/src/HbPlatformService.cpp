// Qt
#include <QtCore/QDebug>
// Local
#include <HbPlatformService.h>
#include <HbPluginInterface.h>
#include <HbPluginInfos.h>
#include <HbPluginService.h>

using namespace hb::plugin;

HbPlatformService::HbPlatformService() :
    QObject(), mPluginManager( this )
{

    mPluginLoaded = false;

    connect(&mPluginManager, &HbPluginManager::pluginLoaded,
            this,            &HbPlatformService::onPluginLoaded, Qt::UniqueConnection );
    connect(&mPluginManager, &HbPluginManager::pluginUnloaded,
            this,            &HbPlatformService::onPluginUnloaded, Qt::UniqueConnection );
}

HbPlatformService::~HbPlatformService()
{

}

void HbPlatformService::loadPlugins  ( const QString & plugin_folder )
{
    if( !mPluginLoaded )
    {
        mPluginManager.load( plugin_folder );
        mPluginLoaded = true;
    }
}

void HbPlatformService::unloadPlugins()
{
    if( mPluginLoaded )
    {
        mPluginManager.unload();
        mPluginLoaded = false;
    }
}

const QList< const HbPluginInfos * > HbPlatformService::pluginInfoList()
{
    return mPluginManager.pluginInfoList();
}

HbPluginService * HbPlatformService::requestService( const QString & service_name ) const
{
    if( mServices.contains( service_name ) && mServices.value( service_name ) )
    {
        return mServices.value( service_name );
    }

    return 0;
}

void HbPlatformService::registerService( HbPluginService * service )
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

const HbPluginInterface *HbPlatformService::requestPlugin( const QString & name )   const
{
    return mPluginManager.plugin( name );
}

QString HbPlatformService::isServiceRegistered( const QString & service_name ) const
{
    if(mServices.contains( service_name ) && mServices.value( service_name ) )
    {
        return mServices.value( service_name )->version();
    }

    return "-1";
}

void HbPlatformService::onPluginLoaded  ( const HbPluginInfos * plugin_infos )
{
    if( !plugin_infos ) return;

    emit pluginLoaded( plugin_infos );
}

void HbPlatformService::onPluginUnloaded( const QString & plugin_name )
{
    emit pluginUnloaded( plugin_name );
}

void HbPlatformService::onLoadPluginRequest  ( const QString & plugin_name )
{
    qDebug() << QString("Load request (plugin=%1)").arg( plugin_name );
    mPluginManager.loadPluginFromName( plugin_name );
}

void HbPlatformService::onUnloadPluginRequest( const QString & plugin_name )
{
    qDebug() << QString( "Unload request (plugin=%1)" ).arg( plugin_name );
    mPluginManager.unloadPlugin( plugin_name );
}
