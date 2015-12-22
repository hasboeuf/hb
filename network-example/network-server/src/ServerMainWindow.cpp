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
#include <ServerSumChannel.h>
#include <ServerChatChannel.h>


using namespace hb::log;
using namespace hb::link;
using namespace hb::network;
using namespace hb::networkexample;

QString ServerMainWindow::msClientId = "940633959281250";                      // Fake value.
QString ServerMainWindow::msClientSecret = "74621eedf9aa2cde9cd31dc5c4d3c440"; // Fake value.

ServerMainWindow::ServerMainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    // Log
    /*QString error;
    if( HbLogService::outputs()->addConsoleOutput( &error ) == 0 )
    {
        printf( "HbLog error: %s", HbLatin1( error ) );
    }*/

    HbLogBegin();

    HbO2ServerConfig facebook_config;
    facebook_config.setClientId( msClientId );
    facebook_config.setClientSecret( msClientSecret );

    HbGeneralServerConfig config;
    config.setAppName("hb-network-example");
    config.setProtocolVersion( 1 );
    config.auth().setAuthMaxTries( 3 );
    config.auth().setAuthTimeout( 300 );
    config.auth().enableFacebookAuth( facebook_config );
    config.presence().setKickAliveThreshold( 20 );
    config.presence().setWarningAliveThreshold( 10 );

    mpHbServer    = new HbServer( config );

    mpSumChannel  = new ServerSumChannel();
    mpChatChannel = new ServerChatChannel();

    // Ui
    setupUi(this);
    setWindowTitle("Server");

    connect(ui_qpb_start, &QPushButton::clicked, this, &ServerMainWindow::onStartClicked);
    connect(ui_qpb_stop,  &QPushButton::clicked, this, &ServerMainWindow::onStopClicked);

    connect( mpHbServer, &HbServer::serverStatusChanged, this, &ServerMainWindow::onServerStatusChanged );

    HbLogEnd();
}

ServerMainWindow::~ServerMainWindow()
{
    HbLogBegin();

    HbLogEnd();
}

void ServerMainWindow::onStartClicked()
{
    HbLogBegin();

    HbTcpServerConfig config;
    config.setAddress(QHostAddress::Any);
    config.setPort( 4000 );
    config.setMaxUsersPerThread( 1 );
    config.setBadHeaderTolerant( false );

    config.assignChannel( mpSumChannel  );
    config.assignChannel( mpChatChannel );

    networkuid server_uid = mpHbServer->joinTcpServer( config, true );
    if( server_uid > 0 )
    {
        HbInfo( "Server %d started.", server_uid );
    }

    HbLogEnd();
}

void ServerMainWindow::onStopClicked()
{
    HbLogBegin();

    mpHbServer->leave();

    HbLogEnd();
}

void ServerMainWindow::onServerStatusChanged( networkuid server_uid, HbNetworkProtocol::ServerStatus status )
{
    HbInfo( "Status changed on server %d: %s.", server_uid, HbLatin1( HbNetworkProtocol::MetaServerStatus::toString( status ) ) );
}

