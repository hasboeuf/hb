// Qt
#include <QtCore/QCoreApplication>
// Hb
#include <HbGlobal.h>
#include <HbLogService.h>
#include <core/HbApplicationHelper.h>
// Local
#include <ServerMainWindow.h>

using hb::networkexample::ServerMainWindow;

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    if (argc >= 3) {
        hb::networkexample::ServerMainWindow::msClientId = QString(argv[1]);
        hb::networkexample::ServerMainWindow::msClientSecret = QString(argv[2]);
    } else {
        std::cout << "Missing args." << std::endl;
    }

    hb::tools::HbApplicationHelper::initApp("hb-io", "hb-io.com");
    hb::tools::HbApplicationHelper::initSkin("fusion");

    hb::log::HbLogService::install("%{level} %{message}");
    hb::log::HbLogService::addConsoleOutput();
    hb::log::HbLogService::processArgs(a.arguments());

    ServerMainWindow w;
    w.show();

    return a.exec();
}
