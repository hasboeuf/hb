#ifndef APPABSTRACTPLUGIN_H
#define APPABSTRACTPLUGIN_H

// Hb
#include <IHbPlugin.h>
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
        using hb::plugin::IHbPlugin;

        class AppAbstractPlugin : public IHbPlugin
        {

        public:
            explicit AppAbstractPlugin();
            virtual ~AppAbstractPlugin();

            virtual PluginInitState init  ( const HbPlatformService * platform_service );
            virtual void            unload() = 0;

        protected:
            const AppPlatformService * mpPlatformService;
        };
    }
}

Q_DECLARE_INTERFACE( hb::pluginexample::AppAbstractPlugin, "hb::pluginexample::AppAbstractPlugin" )

#endif // APPABSTRACTPLUGIN_H
