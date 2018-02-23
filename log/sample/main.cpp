// Qt
#include <QtCore/QCoreApplication>
// Hb
#include <core/HbApplicationHelper.h>
#include <HbLogService.h>
#include <HbLoggerOutputs.h>
// Local


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    hb::tools::HbApplicationHelper::initApp( "hb-io", "hb-io.com" );
    hb::tools::HbApplicationHelper::catchInterruptingEvents();

    hb::log::HbLogService::install("%{level} %{message}");
    hb::log::HbLogService::outputs()->addConsoleOutput();

    qDebug() << "This is a debug trace";
    qInfo() << "This is a info trace";
    qWarning() << "This is a warning trace";
    qCritical() << "This is a critical trace";
    //qFatal("This is a fatal trace");

    return 0;
}
