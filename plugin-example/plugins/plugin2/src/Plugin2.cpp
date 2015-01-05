// Qt
#include <QtCore/QDebug>
#include <QtWidgets/QAction>
#include <QtWidgets/QMessageBox>
// Hb
#include "AppPlatformService.h"
#include "MenuService.h"
// Local
#include "Plugin2.h"



Q_PLUGIN_METADATA(IID "hb::pluginexample::AppPluginInterface")

using namespace hb::pluginexample;

Plugin2::Plugin2() :
    QObject(), AppPluginInterface()
{
}

Plugin2::~Plugin2()
{
}

// TODO visibility of PlatformService methods.

HbPluginInterface::PluginInitState Plugin2::init(const HbPlatformService *platform_service)
{
    MenuService* service_menu = dynamic_cast<MenuService*>(platform_service->requestService("ServiceMenuBar"));
    if(!service_menu)
    {
        return INIT_FAIL;
    }

    QAction* action = service_menu->addItem(MenuService::MENU_PLUGINS, "Plugin2 action");

    if(action)
    {
        connect(action, &QAction::triggered, this, &Plugin2::onAction1Triggered);
    }

    return INIT_SUCCESS;

}

void Plugin2::unload()
{

}

void Plugin2::onAction1Triggered()
{
    qDebug() << "Action1 triggered";
}

bool Plugin2::makeSomething() const
{
    QMessageBox::information(0, "Yeahhh", "Fuck yeahhh from plugin 2", QMessageBox::Ok);
    return true;
}
