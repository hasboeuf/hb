#ifndef APPPLUGININTERFACE_HPP
#define APPPLUGININTERFACE_HPP

#include "PluginInterface.hpp"

class AppPluginInterface : public PluginInterface
{

public:
    explicit AppPluginInterface();
    virtual ~AppPluginInterface();

    virtual PluginInitState init  (const PlatformService* platform_service) = 0;
    virtual void            unload()                                        = 0;

protected:
    const PlatformService* mpPlatformService;
};

Q_DECLARE_INTERFACE(AppPluginInterface, "AppPluginInterface")

#endif // APPPLUGININTERFACE_HPP
