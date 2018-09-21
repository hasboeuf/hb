// System
#include <iostream>
// Qt
#include <QtCore/QChar>
#include <QtCore/QCoreApplication>
#include <QtCore/QTimer>
// Hb
#include <HbLogService.h>
#include <core/HbApplicationHelper.h>
// Local

int main(int argc, char* argv[]) {
    QCoreApplication a(argc, argv);

    hb::tools::HbApplicationHelper::initApp("hb-io", "hb-io.com");

    hb::log::HbLogService::install("%{level} %{message}");
    hb::log::HbLogService::addConsoleOutput();
    hb::log::HbLogService::processArgs(a.arguments());

    QTimer::singleShot(0, &a, [&a]() {
        qDebug() << "This is a debug trace";
        qInfo() << "This is a info trace";
        qWarning() << "This is a warning trace";
        qCritical() << "This is a critical trace";
        // qFatal("This is a fatal trace");

        QTextStream stream(stdin);
        QString line;
        while (stream.readLineInto(&line)) {
            if (line.isNull()) {
                continue;
            }

            if (line.isEmpty()) {
                qDebug() << "Exiting...";
                a.quit();
                break;
            }

            qDebug() << line;
        }
    });

    return a.exec();
}
