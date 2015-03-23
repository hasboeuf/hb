// Qt
#include <QtCore/QDebug>
#include <QtWidgets/QAction>
// Hb
#include <AppPlatformService.h>
#include <MenuService.h>
// Local
#include <Plugin1.h>


Q_PLUGIN_METADATA(IID "hb::pluginexample::AppPluginInterface")

using namespace hb::pluginexample;

Plugin1::Plugin1() :
    QObject(), AppPluginInterface()
{
}

Plugin1::~Plugin1()
{
}

// TODO visibility of PlatformService methods.

HbPluginInterface::PluginInitState Plugin1::init( const HbPlatformService * platform_service )
{

    if(AppPluginInterface::init(platform_service) != INIT_SUCCESS)
    {
        return INIT_FAIL;
    }

    MenuService * service_menu = dynamic_cast< MenuService * >(mpPlatformService->requestService( "ServiceMenuBar" ) );
    if( !service_menu )
    {
        return INIT_FAIL;
    }

    int menu_root = service_menu->addMenu( MenuService::MENU_NEW, "Plugin1" );

    QAction * action = service_menu->addItem( menu_root, "Action1" );

    if( action )
    {
        connect( action, &QAction::triggered, this, &Plugin1::onAction1Triggered );
    }

    return INIT_SUCCESS;

}

void Plugin1::unload()
{

}

void Plugin1::onAction1Triggered()
{
    qDebug() << "Action1 triggered";
    const IPlugin2* plugin = dynamic_cast< const IPlugin2 * >( mpPlatformService->requestPlugin( "Plugin2" ) );

    if( plugin )
    {
        plugin->doSomething();
    }
}
