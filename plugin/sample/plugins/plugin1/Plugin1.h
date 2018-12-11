#ifndef PLUGIN1_H
#define PLUGIN1_H

// Qt
#include <QtCore/QObject>
// Local
#include <../plugin2/IPlugin2.h>
#include <AppAbstractPlugin.h>

namespace hb {
namespace pluginexample {
class Plugin1 : public QObject, public AppAbstractPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Plugin1" FILE "Plugin1.json")
    Q_INTERFACES(hb::pluginexample::AppAbstractPlugin)

public:
    explicit Plugin1();
    virtual ~Plugin1();

    virtual PluginInitState init(const HbPluginPlatform* platform_service);
    virtual void unload();

    void onAction1Triggered();
};
} // namespace pluginexample
} // namespace hb

#endif // PLUGIN1_H
