// Qt
#include <QtWidgets/QFileDialog>
// Local
#include <AppMainWindow.h>
#include <AppPlatformService.h>
#include <MenuService.h>

using namespace hb::plugin;
using namespace hb::pluginexample;

AppMainWindow::AppMainWindow(QWidget* parent) : QMainWindow(parent) {
    setupUi(this);

    AppService* menu_service = new MenuService(menuBar());
    mPlatformServices.registerService(menu_service);

    connect(&mPlatformServices,
            &HbPluginPlatform::pluginStateChanged,
            plw_plugins,
            &HbPluginListWidget::onPluginStateChanged);

    connect(plw_plugins,
            &HbPluginListWidget::loadPluginRequest,
            &mPlatformServices,
            &HbPluginPlatform::onLoadPluginRequest);
    connect(plw_plugins,
            &HbPluginListWidget::unloadPluginRequest,
            &mPlatformServices,
            &HbPluginPlatform::onUnloadPluginRequest);

    connect(qpb_load, &QAbstractButton::clicked, this, &AppMainWindow::onLoadClicked);
    connect(qpb_unload, &QAbstractButton::clicked, this, &AppMainWindow::onUnloadClicked);
}

void AppMainWindow::onLoadClicked() {
    QString plugin_dir = QFileDialog::getExistingDirectory(
        this, "Select a plugin folder", QCoreApplication::applicationDirPath(), QFileDialog::ShowDirsOnly);
    if (plugin_dir.isEmpty()) {
        return;
    }

    mPlatformServices.loadPlugins(plugin_dir);
}

void AppMainWindow::onUnloadClicked() {
    mPlatformServices.unloadPlugins();
}
