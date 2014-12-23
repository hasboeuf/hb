#ifndef PLUGIN1_HPP
#define PLUGIN1_HPP

#include "AppPluginInterface.hpp"
#include "IPlugin2.hpp"

#include <QtCore/QObject>

class Plugin1 : public QObject, public AppPluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "AppPluginInterface" FILE "Plugin1.json")
    Q_INTERFACES(AppPluginInterface)

public:
    explicit Plugin1();
    virtual ~Plugin1();

    virtual PluginInitState init  (const PlatformService* platform_service);
    virtual void            unload();

signals:

public slots:
    void onAction1Triggered();
};

#endif // PLUGIN1_HPP
