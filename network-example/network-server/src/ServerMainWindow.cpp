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
#include <HbServer.h>
// Local
#include <ServerMainWindow.h>


using namespace hb::log;
using namespace hb::network;
using namespace hb::networkexample;

ServerMainWindow::ServerMainWindow(QWidget *parent) :
    QMainWindow(parent)
{

	mpLogWidget = new HbLogWidget(this);
    mpLogWidget->hide();
    q_assert(HbLogService::outputs()->addGuiOutput(HbLogService::outputs()->unusedId(), mpLogWidget->logNotifier())); // TODO Notifier must be handle by hblog ???

    HbLogBegin();


    HbGeneralConfig config;
    config.setAppName("hb-network-example");
    config.setProtocolVersion( 1 );

    mpHbServer = new HbServer( config );

    // Ui
    setupUi(this);
    setWindowTitle("Server");

    // Internal connects
    connect(ui_qa_logs,   &QAction::triggered,   this, &ServerMainWindow::showLogs);
    connect(ui_qpb_start, &QPushButton::clicked, this, &ServerMainWindow::onStartClicked);
    connect(ui_qpb_stop,  &QPushButton::clicked, this, &ServerMainWindow::onStopClicked);



    HbLogEnd();
}

ServerMainWindow::~ServerMainWindow()
{
    HbLogBegin();

    if (mpLogWidget) delete mpLogWidget;

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

    HbTcpServerConfig config;
    config.setAddress(QHostAddress::Any);
    config.setPort( 4000 );
    config.setMaxUsersPerThread( 1 );

    HbNetworkConfig::Timeout timeout;
    timeout.connection    = 1000;
    timeout.reconnection  = 1000;
    timeout.disconnection = 1000;

    config.setTimeout(timeout);

    //mTcpServer.setConfiguration( config );
    //mTcpServer.join();

    mpHbServer->joinTcpServer( config );

    HbLogEnd();
}

void ServerMainWindow::onStopClicked()
{
    HbLogBegin();

    //mTcpServer.leave();
    mpHbServer->leave();

    HbLogEnd();
}
