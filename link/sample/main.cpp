// Qt
#include <QtWidgets/QApplication>
#include <QtCore/QDebug>
// Hb
#include <core/HbApplicationHelper.h>
#include <HbLogService.h>
// Local
#include <LinkMainWindow.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if( argc >= 3 )
    {
        hb::linkexample::LinkMainWindow::msClientId     = QString( argv[1] );
        hb::linkexample::LinkMainWindow::msClientSecret = QString( argv[2] );
    }
    else
    {
        std::cout << "Missing args." << std::endl;
    }

    hb::tools::HbApplicationHelper::initApp( "hb-io", "hb-io.com" );
    hb::tools::HbApplicationHelper::initSkin( "fusion" );
    hb::log::HbLogService::install("%{level} %{message}");
    hb::log::HbLogService::addConsoleOutput();
    hb::log::HbLogService::processArgs( a.arguments() );

    hb::linkexample::LinkMainWindow w;

    w.show();

    return a.exec();
}
