// Local
#include <AppAbstractPlugin.h>

using namespace hb::plugin;
using namespace hb::pluginexample;

AppAbstractPlugin::AppAbstractPlugin() :
    IHbPlugin()
{
    mpPlatformService = 0;
}

AppAbstractPlugin::~AppAbstractPlugin()
{

}

IHbPlugin::PluginInitState AppAbstractPlugin::init( const HbPlatformService * platform_service )
{
    if( !platform_service )
    {
        return INIT_FAIL;
    }

    const AppPlatformService * app_platform_service = dynamic_cast< const AppPlatformService * >( platform_service );

    if( !app_platform_service )
    {
        return INIT_FAIL;
    }

    mpPlatformService = app_platform_service;

    return INIT_SUCCESS;
}
