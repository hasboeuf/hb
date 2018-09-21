// Qt
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
// Hb
#include <HbGlobal.h>
#include <HbLogService.h>
#include <core/HbApplicationHelper.h>
// Local
#include <LogViewerMainWindow.h>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    hb::tools::HbApplicationHelper::initApp("hb-io", "hb-io.com");

    hb::log::HbLogService::processArgs(a.arguments());
    hb::log::HbLogService::addConsoleOutput();

    hb::logviewer::LogViewerMainWindow w;
    w.show();

    return a.exec();
}
