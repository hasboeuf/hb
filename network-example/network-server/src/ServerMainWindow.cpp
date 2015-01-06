// Qt
#include <QtCore/QThread>
#include <QtCore/QSortFilterProxyModel>
#include <QtCore/QDebug>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMessageBox>
#include <QtGui/QCloseEvent>
#include <QtGui/QStandardItemModel>
// Hb
#include <HbGlobal.h>
//#include <HbNetGlobal.h>
#include <HbLogService.h>
#include <gui/HbLogWidget.h>
#include <HbLoggerOutputs.h>

#include <tcp/HbTcpServer.h>
// Local
#include <ServerMainWindow.h>


using namespace hb::log;
using namespace hb::network;
using namespace hb::networkexample;

ServerMainWindow::ServerMainWindow(QWidget *parent) :
    QMainWindow(parent)
{

	mpLogWidget = new HbLogWidget(this);
	q_assert(HbLogService::outputs()->addGuiOutput(HbLogService::outputs()->unusedId(), mpLogWidget->logNotifier())); // TODO Notifier must be handle by hblog ???

	mpTcpServer = nullptr;

    HbLogBegin();

    // Ui
    setupUi(this);
    setWindowTitle("Server");

    ui_qpb_start->setText("Start");

    // Internal connects
    connect(ui_qa_logs, &QAction::triggered,     this, &ServerMainWindow::showLogs);
    connect(ui_qpb_start, &QPushButton::clicked, this, &ServerMainWindow::onStartClicked);

    HbLogEnd();
}

ServerMainWindow::~ServerMainWindow()
{
    HbLogBegin();

    if (mpLogWidget) delete mpLogWidget;
    if (mpTcpServer) delete mpTcpServer;

    HbLogEnd();
}

void ServerMainWindow::init()
{
    HbLogBegin();


    HbLogEnd();
}

void ServerMainWindow::showLogs(bool visible)
{
    mpLogWidget->setVisible(visible);
}

void ServerMainWindow::onStartClicked()
{
    HbLogBegin();

/*
    if(ui_qpb_start->text() == "Start")
    {
        ui_qpb_start->setText("Starting...");

        init();

		if (!mpTcpServer)
		{
			mpTcpServer = new HbTcpServer(this);

			HbTcpServerConfig config;
			config.setAddress(QHostAddress::Any);
			config.setPort(4000);
			config.setMaxUsersPerThread( 1 );

			HbNetworkConfig::Timeout timeout;
			timeout.connection    = 1000;
			timeout.reconnection  = 1000;
			timeout.disconnection = 1000;

			config.setTimeout(timeout);

			mpTcpServer->setConfiguration( config );
			mpTcpServer->join();
			
		}
    }
    else if(ui_qpb_start->text() == "Stop")
    {
        ui_qpb_start->setText("Stopping...");

    }
*/
    HbLogEnd();
}
