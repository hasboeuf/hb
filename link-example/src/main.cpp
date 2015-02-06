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

    hb::tools::HbApplicationHelper::initApp("hb-company", "hb-company.com");
    hb::tools::HbApplicationHelper::initSkin("fusion");
    hb::log::HbLogService::processArgs( argc, argv );

    hb::linkexample::LinkMainWindow w;
    w.show();

	return a.exec();
}
