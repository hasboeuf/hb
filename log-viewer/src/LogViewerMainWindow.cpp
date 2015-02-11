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

	q_assert(HbLogService::outputs()->addGuiOutput(HbLogService::outputs()->unusedId(), qw_log->logNotifier()));


    /*for( int i = 0; i < 40; ++i )
    {
        hb::tools::HbSteadyDateTime time1 = hb::tools::HbSteadyDateTime::now();
        hb::tools::HbSteadyDateTime time2 = hb::tools::HbSteadyDateTime::now();
        qDebug() << time1.toString( "HH:mm:ss.zzz.uuuuuu" );
        //hb::tools::HbSteadyDateTime time2 = hb::tools::HbSteadyDateTime::fromEpoch( time.sinceEpoch() );
        qDebug() << time2.toString( "HH:mm:ss.zzz.uuuuuu" );
        qDebug() << "------------";
    }*/

    HbSteadyDateTime time1 = HbSteadyDateTime::now();
    HbSteadyDateTime time2 = HbSteadyDateTime::fromString( "yyyy-MM-dd hh:mm:ss.zzz.uuu", time1.toString( "yyyy-MM-dd hh:mm:ss.zzz.uuu" ) );

    HbError( "time1=%s (%lld)", HbLatin1( time1.toString( "hh:mm:ss.zzz.uuuuuu" ) ), time1.toNsSinceEpoch() );
    HbError( "time2=%s (%lld)", HbLatin1( time2.toString( "hh:mm:ss.zzz.uuuuuu" ) ), time2.toNsSinceEpoch() );

}
