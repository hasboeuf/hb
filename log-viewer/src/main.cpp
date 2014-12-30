// Qt
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
// Hb
#include <HbGlobal.h>
#include <HbLogService.h>
#include <HbApplicationHelper.h>
// Local
#include <LogViewerMainWindow.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	hb::tools::HbApplicationHelper::initApp("hb-company", "hb-company.com");

    hb::log::HbLogService::processArgs(argc, argv);

	hb::logviewer::LogViewerMainWindow w;
	w.show();

	return a.exec();
}
