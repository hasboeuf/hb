// Qt
#include <QtCore/QCoreApplication>
// Hb
#include <HbGlobal.h>
#include <HbLogService.h>
#include <core/HbApplicationHelper.h>
// Local
#include <ComServerMainWindow.h>

using hb::comexample::ComServerMainWindow;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    hb::tools::HbApplicationHelper::initApp("hb-company", "hb-company.com");
    hb::tools::HbApplicationHelper::initSkin("fusion");

    hb::log::HbLogService::processArgs(argc, argv);

    ComServerMainWindow w;
    w.show();

    return a.exec();
}

