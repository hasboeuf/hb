#ifndef PLUGIN2_H
#define PLUGIN2_H

// Qt
#include <QtCore/QObject>
// Local
#include <AppPluginInterface.h>
#include <IPlugin2.h>

namespace hb
{
    namespace plugin
    {
        class HbPlatformService;
    }

    namespace pluginexample
    {
        class AppPlatformService;

        class Plugin2 : public QObject, public IPlugin2, public AppPluginInterface
        {
            Q_OBJECT
            Q_PLUGIN_METADATA( IID "AppPluginInterface" FILE "Plugin2.json" )
            Q_INTERFACES( hb::pluginexample::AppPluginInterface )

        public:
            explicit Plugin2();
            virtual ~Plugin2();

            virtual PluginInitState init  ( const HbPlatformService * platform_service );
            virtual void            unload();

            bool doSomething() const;
        signals:

        public slots:
            void onAction1Triggered();
        };
    }
}

#endif // PLUGIN2_H
