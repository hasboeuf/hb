// Qt
#include <QtCore/QCoreApplication>
// Hb
#include <HbGlobal.h>
#include <HbLogService.h>
#include <core/HbApplicationHelper.h>
// Local
#include <BasicServerMainWindow.h>

using hb::networkexample::BasicServerMainWindow;

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    hb::tools::HbApplicationHelper::initApp("hb-io", "hb-io.com");
    hb::tools::HbApplicationHelper::initSkin("fusion");

    hb::log::HbLogService::install("%{level} %{message}");
    hb::log::HbLogService::addConsoleOutput();
    hb::log::HbLogService::processArgs(a.arguments());

    BasicServerMainWindow w;
    w.show();

    return a.exec();
}
