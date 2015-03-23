#ifndef APPPLATFORMSERVICE_H
#define APPPLATFORMSERVICE_H

// Hb
#include <HbPlatformService.h>
// Local
#include <AppService.h>

namespace hb
{
    namespace pluginexample
    {
        using hb::plugin::HbPlatformService;

        class AppPlatformService : public HbPlatformService
        {
            Q_OBJECT


        public:
            enum ServiceID
            {
                SERVICE_MENU_BAR,
                SERVICE_TAB
            };

            static QString serviceName( ServiceID service_id );

            explicit AppPlatformService();
            virtual ~AppPlatformService();

            virtual AppService * requestService ( const QString & service_name ) const;


        };
    }
}

#endif // APPPLATFORMSERVICE_H
