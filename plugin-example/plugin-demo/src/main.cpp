// Qt
#include <QtCore/QDebug>
#include <QtWidgets/QApplication>
// Hb
#include <core/HbApplicationHelper.h>
#include <HbLogService.h>
// Local
#include <AppMainWindow.h>

using hb::pluginexample::AppMainWindow;

int main(int argc, char *argv[])
{
    QApplication a( argc, argv );

    hb::tools::HbApplicationHelper::initApp( "hb-io", "hb-io.com" );
    hb::tools::HbApplicationHelper::initSkin("fusion");
    hb::log::HbLogService::processArgs( argc, argv );

    AppMainWindow w;
    w.show();
    
    return a.exec();
}
