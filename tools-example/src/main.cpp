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

    hb::tools::HbApplicationHelper::initApp ( "hb-io", "hb-io.com" );
    hb::tools::HbApplicationHelper::initSkin( "fusion" );
    hb::log::HbLogService::processArgs( argc, argv );

    hb::toolsexample::ToolsMainWindow w;
    w.show();

    return a.exec();
}
