// Qt
#include <QtCore/QDebug>
#include <QtWidgets/QAction>
// Hb
#include <AppPlatformService.h>
#include <MenuService.h>
// Local
#include <Plugin1.h>

Q_PLUGIN_METADATA(IID "hb::pluginexample::AppAbstractPlugin")

using namespace hb::pluginexample;

Plugin1::Plugin1() : QObject(), AppAbstractPlugin() {
}

Plugin1::~Plugin1() {
}

IHbPlugin::PluginInitState Plugin1::init(const HbPluginPlatform* platform_service) {
    if (AppAbstractPlugin::init(platform_service) != INIT_SUCCESS) {
        return INIT_FAIL;
    }

    MenuService* service_menu =
        dynamic_cast<MenuService*>(mpPlatformService->requestService(AppPlatformService::SERVICE_MENU_BAR));
    if (!service_menu) {
        return INIT_FAIL;
    }

    int menu_root = service_menu->addMenu(MenuService::MENU_NEW, "Plugin1");

    QAction* action = service_menu->addItem(menu_root, "Action1");

    if (action) {
        connect(action, &QAction::triggered, this, &Plugin1::onAction1Triggered);
    }

    return INIT_SUCCESS;
}

void Plugin1::unload() {
    qDebug() << "Plugin1::unload!";
    //! \todo Remove menu.
}

void Plugin1::onAction1Triggered() {
    const IPlugin2* plugin = dynamic_cast<const IPlugin2*>(mpPlatformService->requestPlugin("Plugin2"));

    if (plugin) {
        plugin->doSomething();
    }
}
