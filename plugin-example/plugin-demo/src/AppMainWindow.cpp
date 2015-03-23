// Local
#include <AppMainWindow.h>
#include <AppPlatformService.h>
#include <MenuService.h>

using namespace hb::plugin;
using namespace hb::pluginexample;

AppMainWindow::AppMainWindow(const QString & plugin_dir, QWidget * parent ) :
    QMainWindow(parent)
{
    setupUi(this);

    connect( &mPlatformServices, &HbPlatformService::pluginLoaded,   plw_plugins, &HbPluginListWidget::onPluginLoaded   );
    connect( &mPlatformServices, &HbPlatformService::pluginUnloaded, plw_plugins, &HbPluginListWidget::onPluginUnloaded );

    connect( plw_plugins, &HbPluginListWidget::loadPluginRequest,   &mPlatformServices, &HbPlatformService::onLoadPluginRequest   );
    connect( plw_plugins, &HbPluginListWidget::unloadPluginRequest, &mPlatformServices, &HbPlatformService::onUnloadPluginRequest );

    plw_plugins->setPlugins( mPlatformServices.pluginInfoList() );

    AppService * menu_service = new MenuService( AppPlatformService::serviceName( AppPlatformService::SERVICE_MENU_BAR ), "0.0.1", menuBar() );

    mPlatformServices.registerService( menu_service );
    mPlatformServices.loadPlugins( plugin_dir );

    //mPlatformServices.unloadPlugin("HbPlugin2");
}
