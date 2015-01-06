// Qt
#include <QtCore/QCoreApplication>
// Hb
#include <HbGlobal.h>
#include <HbLogService.h>
#include <HbApplicationHelper.h>
// Local
#include <UserMainWindow.h>

using hb::networkexample::UserMainWindow;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	hb::tools::HbApplicationHelper::initApp("hb-company", "hb-company.com");
	hb::tools::HbApplicationHelper::initSkin("fusion");

    hb::log::HbLogService::processArgs(argc, argv);

    UserMainWindow w;
    w.show();

    return a.exec();
}

