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
#include <tcp/HbTcpClient.h>
// Local
#include <UserMainWindow.h>


using namespace hb::log;
using namespace hb::network;
using namespace hb::networkexample;

UserMainWindow::UserMainWindow(QWidget *parent) :
    QMainWindow(parent)
{

	mpLogWidget = new HbLogWidget(this);
	q_assert(HbLogService::outputs()->addGuiOutput(HbLogService::outputs()->unusedId(), mpLogWidget->logNotifier())); // TODO Notifier must be handle by hblog ???

    mStarted = false;

    HbLogBegin();

    // Ui
    setupUi(this);
    setWindowTitle("User");

    ui_qpb_start->setText("Start");

    connect(&mTcpClient, &HbTcpClient::connected,    this, &UserMainWindow::onClientConnected);
    connect(&mTcpClient, &HbTcpClient::disconnected, this, &UserMainWindow::onClientDisconnected);

    // Internal connects
    connect(ui_qa_logs,   &QAction::triggered,   this, &UserMainWindow::showLogs);
    connect(ui_qpb_start, &QPushButton::clicked, this, &UserMainWindow::onStartClicked);

    HbLogEnd();
}

UserMainWindow::~UserMainWindow()
{
    HbLogBegin();

    if (mpLogWidget) delete mpLogWidget;

    HbLogEnd();
}

void UserMainWindow::init()
{
    HbLogBegin();
    HbLogEnd();
}


void UserMainWindow::showLogs(bool visible)
{
    mpLogWidget->setVisible(visible);
}

void UserMainWindow::onClientConnected()
{
    HbLogBegin();
    mStarted = true;
    ui_qpb_start->setText("Stop");
    HbLogEnd();
}

void UserMainWindow::onClientDisconnected()
{
    HbLogBegin();
    mStarted = false;
    ui_qpb_start->setText("Start");
    HbLogEnd();
}

void UserMainWindow::onStartClicked()
{
    HbLogBegin();

    if( !mStarted )
    {

        ui_qpb_start->setText("Starting...");

        HbTcpConfig config;
        config.setAddress(QHostAddress::LocalHost);
        config.setPort(4000);

        HbNetworkConfig::Timeout timeout;
        timeout.connection    = 10;
        timeout.reconnection  = 0;
        timeout.disconnection = 10;

        config.setTimeout(timeout);

        mTcpClient.setConfiguration(config);
        mTcpClient.join();
			
    }
    else
    {
        ui_qpb_start->setText("Stopping...");

        mTcpClient.leave();
    }

    HbLogEnd();
}
