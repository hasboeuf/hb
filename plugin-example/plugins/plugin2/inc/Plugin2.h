#ifndef PLUGIN2_H
#define PLUGIN2_H

// Qt
#include <QtCore/QObject>
// Local
#include <AppPluginInterface.h>
#include <IPlugin2.h>

namespace hb
{
    namespace pluginexample
    {
        class Plugin2 : public QObject, public IPlugin2, public AppPluginInterface
        {
            Q_OBJECT
            Q_PLUGIN_METADATA(IID "AppPluginInterface" FILE "Plugin2.json")
            Q_INTERFACES(AppPluginInterface)

        public:
            explicit Plugin2();
            virtual ~Plugin2();

            virtual PluginInitState init  (const PlatformService* platform_service);
            virtual void            unload();

            bool makeSomething() const;
        signals:

        public slots:
            void onAction1Triggered();
        };
    }
}

#endif // PLUGIN2_H
