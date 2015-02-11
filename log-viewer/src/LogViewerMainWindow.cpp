// Qt
#include <QtCore/QDebug>
#include <QtWidgets/QApplication>
// Hb
#include <HbLogService.h>
#include <HbLoggerInputs.h>
#include <HbLoggerOutputs.h>
#include <core/HbSteadyDateTime.h>
// Local
#include <LogViewerMainWindow.h>

using namespace hb::logviewer;
using namespace hb::log;
using namespace hb::tools;


LogViewerMainWindow::LogViewerMainWindow( QWidget * parent ) : 
    QMainWindow( parent )
{
	setupUi(this);

    q_assert( HbLogService::outputs()->addGuiOutput(HbLogService::outputs()->unusedId(), qw_log->logNotifier() ) );
}
