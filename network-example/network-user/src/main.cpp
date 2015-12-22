// Qt
#include <QtCore/QCoreApplication>
// Hb
#include <HbGlobal.h>
#include <HbLogService.h>
#include <core/HbApplicationHelper.h>
// Local
#include <UserMainWindow.h>

using hb::networkexample::UserMainWindow;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if( argc >= 2 )
    {
        hb::networkexample::UserMainWindow::msClientId = QString( argv[1] );
    }
    else
    {
        std::cout << "Missing args." << std::endl;
    }

    hb::tools::HbApplicationHelper::initApp( "hb-io", "hb-io.com" );
    hb::tools::HbApplicationHelper::initSkin("fusion");

    hb::log::HbLogService::processArgs( argc, argv );

    UserMainWindow w;
    w.show();

    return a.exec();
}

