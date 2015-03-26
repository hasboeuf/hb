// Qt
#include <QtWidgets/QFileDialog>
// Hb
#include <HbLogService.h>
#include <HbLoggerOutputs.h>
// Local
#include <AppMainWindow.h>
#include <AppPlatformService.h>
#include <MenuService.h>

using namespace hb::log;
using namespace hb::plugin;
using namespace hb::pluginexample;

AppMainWindow::AppMainWindow( QWidget * parent ) :
    QMainWindow( parent )
{
    setupUi( this );

    // Log
    QString error;
    if( HbLogService::outputs()->addConsoleOutput( &error ) == 0 )
    {
        printf( "HbLog error: %s", HbLatin1( error ) );
    }

    AppService * menu_service = new MenuService( menuBar() );
    mPlatformServices.registerService( menu_service );

    connect( &mPlatformServices, &HbPlatformService::pluginLoaded,   plw_plugins, &HbPluginListWidget::onPluginLoaded   );
    connect( &mPlatformServices, &HbPlatformService::pluginUnloaded, plw_plugins, &HbPluginListWidget::onPluginUnloaded );

    connect( plw_plugins, &HbPluginListWidget::loadPluginRequest,   &mPlatformServices, &HbPlatformService::onLoadPluginRequest   );
    connect( plw_plugins, &HbPluginListWidget::unloadPluginRequest, &mPlatformServices, &HbPlatformService::onUnloadPluginRequest );

    connect( qpb_load,   &QAbstractButton::clicked, this, &AppMainWindow::onLoadClicked );
    connect( qpb_unload, &QAbstractButton::clicked, this, &AppMainWindow::onUnloadClicked );
}

void AppMainWindow::onLoadClicked  ()
{
    QString plugin_dir = QFileDialog::getExistingDirectory( this,
                                                            "Select a plugin folder",
                                                            QCoreApplication::applicationDirPath(),
                                                            QFileDialog::ShowDirsOnly );
    if( plugin_dir.isEmpty() )
    {
        return;
    }

    mPlatformServices.loadPlugins( plugin_dir );
    //plw_plugins->setPlugins( mPlatformServices.pluginInfoList() );
}

void AppMainWindow::onUnloadClicked()
{
    mPlatformServices.unloadPlugins();
}
