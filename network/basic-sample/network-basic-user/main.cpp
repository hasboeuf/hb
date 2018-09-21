// Qt
#include <QtCore/QCoreApplication>
// Hb
#include <HbGlobal.h>
#include <HbLogService.h>
#include <core/HbApplicationHelper.h>
// Local
#include <BasicUserMainWindow.h>

using hb::networkexample::BasicUserMainWindow;

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    hb::tools::HbApplicationHelper::initApp("hb-io", "hb-io.com");
    hb::tools::HbApplicationHelper::initSkin("fusion");

    hb::log::HbLogService::install("%{level} %{message}");
    hb::log::HbLogService::addConsoleOutput();
    hb::log::HbLogService::processArgs(a.arguments());

    BasicUserMainWindow w;
    w.show();

    return a.exec();
}
