// Qt
#include <QtCore/QCoreApplication>
// Hb
#include <HbGlobal.h>
#include <HbLogService.h>
#include <core/HbApplicationHelper.h>
// Local
#include <BasicServerMainWindow.h>

using hb::networkexample::BasicServerMainWindow;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    hb::tools::HbApplicationHelper::initApp("hb-company", "hb-company.com");
    hb::tools::HbApplicationHelper::initSkin("fusion");

    hb::log::HbLogService::processArgs(argc, argv);

    BasicServerMainWindow w;
    w.show();

    return a.exec();
}

