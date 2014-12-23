// Qt
#include <QtCore/QDebug>
#include <QtWidgets/QApplication>
// Hb
#include <HbLogService.h>
#include <HbLoggerInputs.h>
#include <HbLoggerOutputs.h>
// Local
#include <LogViewerMainWindow.h>

using namespace hb::logviewer;
using namespace hb::log;


LogViewerMainWindow::LogViewerMainWindow( QWidget * parent ) : 
    QMainWindow( parent )
{
	setupUi(this);

	q_assert(HbLogService::outputs()->addGuiOutput(HbLogService::outputs()->unusedId(), qw_log->logNotifier()));

	// Args
	/*QRegExp regex("(local:[a-z]+)|(tcp:[0-9]{1,5})");
	int pos = regex.indexIn(arg);
	if (pos > -1) {
		QString cmd   = regex.cap(0);
		QString type  = cmd.split(":").at(0);
		QString value = cmd.split(":").at(1);

		if (type == "local")
		{
			q_assert(HbLogService::inputs()->addLocalSocketInput(0, value));
			HbInfo("Local socket input added (%s)", HbLatin1(value));
		}
		else
		{
			
			HbInfo("Tcp socket input added (%s)", HbLatin1(value));
		}
	}*/

	HbLogBegin();

	qDebug() << "test";
	qWarning() << "toto";
	qCritical() << "titi";
	
	HbTrace("trace");
	HbDebug("debug");
	HbInfo("info");
	HbWarning("wanring");
	HbError("error");
	HbCritical("critical");

	QString t = QString("%1 %2 %3").arg(QString("Nik")).arg(" sa ").arg("mer.");
	quint8 f = 1;
	HbError("%s %d %d", HbLatin1(t), 69, f);

	HbLogEnd();
}