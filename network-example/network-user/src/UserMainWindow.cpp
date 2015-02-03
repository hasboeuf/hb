// Qt
#include <QtCore/QString>
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
#include <core/HbUuidGenerator.h>
#include <HbLogService.h>
#include <gui/HbLogWidget.h>
#include <HbLoggerOutputs.h>
#include <contract/auth/HbAuthRequestContract.h>
#include <contract/HbNetworkHeader.h>
#include <contract/HbNetworkProtocol.h>
// Local
#include <UserMainWindow.h>


using namespace hb::log;
using namespace hb::network;
using namespace hb::networkexample;

UserMainWindow::UserMainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    mpLogWidget = new HbLogWidget( this );
    mpLogWidget->hide();

    q_assert( HbLogService::outputs()->addGuiOutput( HbLogService::outputs()->unusedId(), mpLogWidget->logNotifier() ) ); // TODO Notifier must be handle by hblog ???

    HbLogBegin();

    // Ui
    setupUi( this );
    setWindowTitle( "User" );

    connect( &mTcpClient, &HbTcpClient::connected,    this, &UserMainWindow::onClientConnected );
    connect( &mTcpClient, &HbTcpClient::disconnected, this, &UserMainWindow::onClientDisconnected );

    // Internal connects
    connect( ui_qa_logs,   &QAction::triggered,   this, &UserMainWindow::showLogs );
    connect( ui_qpb_start, &QPushButton::clicked, this, &UserMainWindow::onStartClicked );
    connect( ui_qpb_stop,       &QPushButton::clicked, this, &UserMainWindow::onStopClicked );
    connect( ui_qpb_connection, &QPushButton::clicked, this, &UserMainWindow::onConnectionRequest );

    init();

    HbLogEnd();
}

UserMainWindow::~UserMainWindow()
{
    HbLogBegin();

    if ( mpLogWidget ) delete mpLogWidget;

    HbLogEnd();
}

void UserMainWindow::init()
{
    HbLogBegin();

    HbLogEnd();
}


void UserMainWindow::showLogs( bool visible )
{
    mpLogWidget->setVisible( visible );
}

void UserMainWindow::onClientConnected()
{
    HbLogBegin();
    HbLogEnd();
}

void UserMainWindow::onClientDisconnected()
{
    HbLogBegin();
    HbLogEnd();
}

void UserMainWindow::onStartClicked()
{
    HbLogBegin();

    HbNetworkProtocol::msAppName = "hb-network-example";
    HbNetworkProtocol::msProtocolVersion = 1;

    HbTcpClientConfig config;
    config.setAddress( QHostAddress::LocalHost );
    config.setPort( 4000 );

    HbTimeoutClientConfig timeout;
    timeout.setReconnectionDelay( 1000 );
    timeout.setTickInterval( 1 );

    config.setTimeout( timeout );

    mTcpClient.setConfiguration( config );
    mTcpClient.join();

    HbLogEnd();
}

void UserMainWindow::onStopClicked()
{
    mTcpClient.leave();
}

void UserMainWindow::onConnectionRequest()
{
    HbLogBegin();

    HbAuthRequestContract contract;
    contract.setUsername( "hasboeuf" );
    contract.setPassword( "motherfucker" );

    mTcpClient.send( &contract );

    HbLogEnd();
}
