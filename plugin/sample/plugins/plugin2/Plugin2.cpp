// Qt
#include <QtCore/QDebug>
#include <QtWidgets/QAction>
#include <QtWidgets/QMessageBox>
// Hb
#include <AppPlatformService.h>
#include <MenuService.h>
// Local
#include <Plugin2.h>

Q_PLUGIN_METADATA(IID "hb::pluginexample::AppAbstractPlugin")

using namespace hb::pluginexample;

Plugin2::Plugin2(QObject* parent) : QObject(parent), AppAbstractPlugin() {
}

Plugin2::~Plugin2() {
}

IHbPlugin::PluginInitState Plugin2::init(const HbPluginPlatform* platform_service) {
    MenuService* service_menu =
        dynamic_cast<MenuService*>(platform_service->requestService(AppPlatformService::SERVICE_MENU_BAR));
    if (!service_menu) {
        return INIT_SUCCESS_PARTIALLY;
    }

    QAction* action = service_menu->addItem(MenuService::MENU_PLUGINS, "Plugin2 action");

    if (action) {
        connect(action, &QAction::triggered, this, &Plugin2::onAction1Triggered);
    }

    return INIT_SUCCESS;
}

void Plugin2::unload() {
    qDebug() << "Plugin2::unload!";
    //! \todo Remove menu.
}

void Plugin2::onAction1Triggered() {
    QMessageBox::information(0, "Yeahhh", "Action1 from plugin 2", QMessageBox::Ok);
}

bool Plugin2::doSomething() const {
    QMessageBox::information(0, "Yeahhh", "Fuck yeahhh from plugin 2", QMessageBox::Ok);
    return true;
}
