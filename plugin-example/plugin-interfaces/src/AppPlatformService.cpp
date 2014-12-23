#include "AppPlatformService.hpp"
#include "AppService.hpp"

AppPlatformService::AppPlatformService()
{
}

AppPlatformService::~AppPlatformService()
{

}

QString AppPlatformService::serviceName(ServiceID service_id)
{
    if(service_id == SERVICE_MENU_BAR)
    {
        return "ServiceMenuBar";
    }
    else if(service_id == SERVICE_TAB)
    {
        return "ServiceTab";
    }
    else
    {
        return "ServiceUnknown";
    }
}

AppService* AppPlatformService::requestService(QString service_name)
{
    Service*    service     = PlatformService::requestService(service_name);

    return dynamic_cast<AppService*>(service);
}
