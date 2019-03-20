// System
#include <stdio.h>
// Qt
#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QTimer>
// Hb
#include <HbLogService.h>
#include <HbPluginService.h>
#include <com/tcp/HbTcpClient.h>
#include <config.h>
#include <core/HbSteadyDateTime.h>
#include <facebook/HbO2ClientFacebook.h>

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);

    qDebug() << "Sample uses hb version" << HB_VERSION_STRING;
    qDebug() << "It is" << hb::tools::HbSteadyDateTime::now().toString("yyyy/MM/dd HH:mm:ss:zzz:uuuuuu");

    hb::log::HbLogService::addConsoleOutput();
    qDebug() << "This is a trace using HbLog";
    hb::link::HbO2ClientFacebook o2Service;
    hb::plugin::HbPluginService pluginService("sample", "1.0.0");
    hb::network::HbTcpClient tcpClient;

    QTimer::singleShot(0, &app, &QCoreApplication::quit);

    return app.exec();
}
