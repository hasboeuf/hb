// Local
#include <AppMainWindow.h>
#include <AppPlatformService.h>
#include <MenuService.h>

AppMainWindow::AppMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

    connect(&mPlatformServices, &PlatformService::pluginLoaded,   plw_plugins, &PluginListWidget::onPluginLoaded);
    connect(&mPlatformServices, &PlatformService::pluginUnloaded, plw_plugins, &PluginListWidget::onPluginUnloaded);

    connect(plw_plugins, &PluginListWidget::loadPluginRequest,   &mPlatformServices, &PlatformService::onLoadPluginRequest);
    connect(plw_plugins, &PluginListWidget::unloadPluginRequest, &mPlatformServices, &PlatformService::onUnloadPluginRequest);

    plw_plugins->setPlugins(mPlatformServices.pluginInfoList());

    Service* menu_service = new MenuService(AppPlatformService::serviceName(AppPlatformService::SERVICE_MENU_BAR), "0.0.1", menuBar());

    mPlatformServices.registerService(menu_service);
    mPlatformServices.loadPlugins(QCoreApplication::applicationDirPath() + "/plugins");

    //mPlatformServices.unloadPlugin("Plugin2");
}
