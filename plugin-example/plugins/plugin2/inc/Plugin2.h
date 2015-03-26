#ifndef PLUGIN2_H
#define PLUGIN2_H

// Qt
#include <QtCore/QObject>
// Local
#include <AppAbstractPlugin.h>
#include <IPlugin2.h>

namespace hb
{
    namespace plugin
    {
        class HbPluginPlatform;
    }

    namespace pluginexample
    {
        class AppPlatformService;

        class Plugin2 : public QObject, public IPlugin2, public AppAbstractPlugin
        {
            Q_OBJECT
            Q_PLUGIN_METADATA( IID "AppAbstractPlugin" FILE "Plugin2.json" )
            Q_INTERFACES( hb::pluginexample::AppAbstractPlugin )

        public:
            explicit Plugin2();
            virtual ~Plugin2();

            virtual PluginInitState init  ( const HbPluginPlatform * platform_service );
            virtual void            unload();

            bool doSomething() const;
        signals:

        public slots:
            void onAction1Triggered();
        };
    }
}

#endif // PLUGIN2_H
