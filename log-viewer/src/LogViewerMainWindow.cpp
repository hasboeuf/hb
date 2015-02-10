// Qt
#include <QtCore/QDebug>
#include <QtWidgets/QApplication>
// Hb
#include <HbLogService.h>
#include <HbLoggerInputs.h>
#include <HbLoggerOutputs.h>
#include <core/HbSteadyTime.h>
// Local
#include <LogViewerMainWindow.h>

using namespace hb::logviewer;
using namespace hb::log;


LogViewerMainWindow::LogViewerMainWindow( QWidget * parent ) : 
    QMainWindow( parent )
{
	setupUi(this);

	q_assert(HbLogService::outputs()->addGuiOutput(HbLogService::outputs()->unusedId(), qw_log->logNotifier()));

    hb::tools::HbSteadyTime t1 = hb::tools::HbSteadyTime::now();
    hb::tools::HbSteadyTime t2 = hb::tools::HbSteadyTime::now();

    QString t1_str = t1.toString( "hh:mm:ss.zzz.uuuuuu" );

    qDebug() << t1_str;
    qDebug() << t2.toString( "hh:mm:ss.zzz.uuuuuu" );

    //hb::tools::HbSteadyTime t3 = hb::tools::HbSteadyTime::fromString( "hh:mm:ss.zzz.uuuuuu", t1_str );

    //qDebug() << t3.toString( "hh:mm:ss.zzz.uuuuuu" );
}
