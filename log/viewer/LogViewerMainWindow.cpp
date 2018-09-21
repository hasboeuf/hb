// Qt
#include <QtCore/QDebug>
#include <QtWidgets/QApplication>
// Hb
#include <HbLogService.h>
#include <core/HbSteadyDateTime.h>
// Local
#include <LogViewerMainWindow.h>

using namespace hb::logviewer;
using namespace hb::log;
using namespace hb::tools;

LogViewerMainWindow::LogViewerMainWindow(QWidget* parent) : QMainWindow(parent) {
    setupUi(this);

    HbLogService::addGuiOutput(qw_log->logNotifier());
}
