#ifndef APPPLUGININTERFACE_H
#define APPPLUGININTERFACE_H

// Hb
#include <HbPluginInterface.h>
// Local
#include <AppPlatformService.h> // Covariance.

namespace hb
{
    namespace plugin
    {
        class HbPlatformService;
    }

    namespace pluginexample
    {
        using hb::plugin::HbPluginInterface;

        class AppPluginInterface : public HbPluginInterface
        {

        public:
            explicit AppPluginInterface();
            virtual ~AppPluginInterface();

            virtual PluginInitState init  ( const HbPlatformService * platform_service );
            virtual void            unload() = 0;

        protected:
            const AppPlatformService * mpPlatformService;
        };
    }
}

Q_DECLARE_INTERFACE( hb::pluginexample::AppPluginInterface, "hb::pluginexample::AppPluginInterface" )

#endif // APPPLUGININTERFACE_H
