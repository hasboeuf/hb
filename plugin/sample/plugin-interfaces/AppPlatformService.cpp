// Hb
#include <HbPluginService.h>
// Local
#include <AppPlatformService.h>
#include <AppService.h>

using namespace hb::pluginexample;
using namespace hb::plugin;

const QString AppPlatformService::SERVICE_MENU_BAR = QStringLiteral( "ServiceMenuBar" );
const QString AppPlatformService::SERVICE_TAB      = QStringLiteral( "ServiceTab" );

AppPlatformService::AppPlatformService() : HbPluginPlatform()
{
}

AppPlatformService::~AppPlatformService() {

}

AppService * AppPlatformService::requestService( const QString & service_name ) const
{
    HbPluginService * service = HbPluginPlatform::requestService( service_name );

    return dynamic_cast< AppService * >( service );
}
