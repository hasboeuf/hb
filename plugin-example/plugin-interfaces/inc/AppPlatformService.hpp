#ifndef APPPLATFORMSERVICE_HPP
#define APPPLATFORMSERVICE_HPP

#include "PlatformService.hpp"

class AppService;

class AppPlatformService : public PlatformService
{
    Q_OBJECT


public:
    enum ServiceID
    {
        SERVICE_MENU_BAR,
        SERVICE_TAB
    };

    static QString serviceName(ServiceID service_id);

    explicit AppPlatformService();
    virtual ~AppPlatformService();

    virtual AppService* requestService (QString service_name);


};

#endif // APPPLATFORMSERVICE_HPP
