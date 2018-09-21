// Qt
#include <QtCore/QDebug>
#include <QtWidgets/QApplication>
// Hb
#include <HbLogService.h>
#include <core/HbApplicationHelper.h>
// Local
#include <AppMainWindow.h>

using hb::pluginexample::AppMainWindow;

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    hb::tools::HbApplicationHelper::initApp("hb-io", "hb-io.com");
    hb::tools::HbApplicationHelper::initSkin("fusion");
    hb::log::HbLogService::install();
    hb::log::HbLogService::addConsoleOutput();
    hb::log::HbLogService::processArgs(a.arguments());

    AppMainWindow w;
    w.show();

    return a.exec();
}
