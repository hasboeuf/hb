#ifndef APPPLATFORMSERVICE_H
#define APPPLATFORMSERVICE_H

// Hb
#include <HbPluginPlatform.h>
// Local
#include <AppService.h>

namespace hb
{
    namespace pluginexample
    {
        using hb::plugin::HbPluginPlatform;

        class AppPlatformService : public HbPluginPlatform
        {
            Q_OBJECT


        public:
            static const QString SERVICE_MENU_BAR;
            static const QString SERVICE_TAB;

            explicit AppPlatformService();
            virtual ~AppPlatformService();

            virtual AppService * requestService ( const QString & service_name ) const;


        };
    }
}

#endif // APPPLATFORMSERVICE_H
