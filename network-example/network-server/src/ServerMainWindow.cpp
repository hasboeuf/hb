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
#include <HbLogService.h>
#include <gui/HbLogWidget.h>
#include <HbLoggerOutputs.h>
#include <HbServer.h>
// Local
#include <ServerMainWindow.h>
#include <ServerAuthStrategy.h>


using namespace hb::log;
using namespace hb::network;
using namespace hb::networkexample;

ServerMainWindow::ServerMainWindow(QWidget *parent) :
    QMainWindow(parent)
{

	mpLogWidget = new HbLogWidget(this);
    mpLogWidget->hide();
    q_assert( HbLogService::outputs()->addGuiOutput( mpLogWidget->logNotifier()) > 0 ); // TODO Notifier must handle by hblog ???

    HbLogBegin();


    HbGeneralServerConfig config;
    config.setAppName("hb-network-example");
    config.setProtocolVersion( 1 );
    config.enableAuthentication< ServerAuthStrategy >();

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

    HbTimeoutServerConfig timeout;
    timeout.setTickInterval( 1 );
    timeout.setWarningThreshold( 5 );
    timeout.setKickThreshold( 10 );

    config.setTimeout( timeout );

    quint16 server_uid = mpHbServer->joinTcpServer( config );
    if( server_uid > 0 )
    {
        HbInfo( "Server #%d started.", server_uid );
    }

    HbLogEnd();
}

void ServerMainWindow::onStopClicked()
{
    HbLogBegin();

    mpHbServer->leave();

    HbLogEnd();
}
