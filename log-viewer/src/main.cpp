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

	QStringList args;
	for (int n = 1; n < argc; ++n) // Skip the program name.
	{
		args.append(QString::fromLatin1(argv[n]));
	}
	hb::log::HbLogService::processArgs(args);

	hb::logviewer::LogViewerMainWindow w;
	w.show();

	return a.exec();
}