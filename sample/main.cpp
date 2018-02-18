// System
#include <stdio.h>
// Qt
#include <QCoreApplication>
#include <QDebug>
// Hb
#include <config.h>
#include <core/HbSteadyDateTime.h>
#include <HbLogService.h>
#include <HbLoggerOutputs.h>
#include <facebook/HbO2ClientFacebook.h>
#include <HbPluginService.h>
#include <com/tcp/HbTcpClient.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "Sample uses hb version" << HB_VERSION_STRING;
    qDebug() << "It is" << hb::tools::HbSteadyDateTime::now().toString("yyyy/MM/dd HH:mm:ss:zzz:uuuuuu");

    hb::log::HbLogService::outputs()->addConsoleOutput();
    HbDebug("This is a trace using HbLog");
    hb::link::HbO2ClientFacebook o2Service;
    hb::plugin::HbPluginService pluginService("sample", "1.0.0");
    hb::network::HbTcpClient tcpClient;

    return a.exec();
}
