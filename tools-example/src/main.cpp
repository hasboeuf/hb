// Qt
#include <QtWidgets/QApplication>
#include <QtCore/QDebug>
// Hb
#include <core/HbApplicationHelper.h>
#include <HbLogService.h>
// Local
#include <ToolsMainWindow.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Q_INIT_RESOURCE( HbLog );

    hb::tools::HbApplicationHelper::initApp ( "hb", "hb-io.com", "hbtest" );
    hb::tools::HbApplicationHelper::initSkin( "fusion" );
    hb::log::HbLogService::processArgs( argc, argv );

    hb::toolsexample::ToolsMainWindow w;
    w.show();

    return a.exec();
}
