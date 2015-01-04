#ifndef PLUGIN1_H
#define PLUGIN1_H

// Qt
#include <QtCore/QObject>
// Local
#include <AppPluginInterface.h>
#include <../../plugin2/inc/IPlugin2.h>

namespace hb
{
    namespace pluginexample
    {
        class Plugin1 : public QObject, public AppPluginInterface
        {
            Q_OBJECT
            Q_PLUGIN_METADATA(IID "Plugin1" FILE "Plugin1.json")
            Q_INTERFACES(hb::pluginexample::AppPluginInterface)

        public:
            explicit Plugin1();
            virtual ~Plugin1();

            virtual PluginInitState init  (const AppPlatformService* platform_service);
            virtual void            unload();

        signals:

        public slots:
            void onAction1Triggered();
        };
    }
}

#endif // PLUGIN1_H
