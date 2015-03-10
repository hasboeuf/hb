// Qt
#include <QtCore/QString>
#include <QtCore/QThread>
#include <QtCore/QSortFilterProxyModel>
#include <QtCore/QDebug>
#include <QtGui/QDesktopServices>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMessageBox>
#include <QtGui/QCloseEvent>
#include <QtGui/QStandardItemModel>
#include <QtCore/QSharedPointer>
// Hb
#include <HbGlobal.h>
#include <HbLogService.h>
#include <gui/HbLogWidget.h>
#include <HbLoggerOutputs.h>
#include <HbClient.h>
#include <contract/auth/HbAuthFacebookRequestContract.h>
#include <contract/HbNetworkHeader.h>
#include <contract/HbNetworkProtocol.h>
#include <facebook/HbO2ClientFacebook.h>
// Local
#include <UserMainWindow.h>

using namespace hb::tools;
using namespace hb::log;
using namespace hb::link;
using namespace hb::network;
using namespace hb::networkexample;

UserMainWindow::UserMainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    // Log
    /*QString error;
    if( HbLogService::outputs()->addConsoleOutput( &error ) == 0 )
    {
        printf( "HbLog error: %s", HbLatin1( error ) );
    }*/

    HbLogBegin();

    // Ui
    setupUi( this );
    setWindowTitle( "User" );

    HbO2ClientConfig facebook_config;
    facebook_config.setClientId( "940633959281250" );
    facebook_config.setLocalPort( 8080 );
    facebook_config.addScope( FB_PERMISSION_EMAIL );
    facebook_config.addScope( FB_PERMISSION_FRIENDS );

    HbGeneralClientConfig config;
    config.setAppName( "hb-network-example" );
    config.setProtocolVersion( 1 );
    config.auth().enableFacebookAuth( facebook_config );
    config.presence().setKeepAliveInterval( 4 );

    mpHbClient       = new HbClient( config );

    connect( ui_qpb_start,             &QPushButton::clicked, this, &UserMainWindow::onStartClicked );
    connect( ui_qpb_stop,              &QPushButton::clicked, this, &UserMainWindow::onStopClicked );
    //connect( ui_qpb_user_connection, &QPushButton::clicked, this, &UserMainWindow::onUserConnectionRequest );
    connect( ui_qpb_fb_authentication, &QPushButton::clicked, this, &UserMainWindow::onFacebookConnectionRequest );

    connect( mpHbClient, &HbClient::clientStatusChanged, this, &UserMainWindow::onClientStatusChanged );
    connect( mpHbClient, &HbClient::meStatusChanged,     this, &UserMainWindow::onMeStatusChanged );

    HbLogEnd();
}

UserMainWindow::~UserMainWindow()
{
    HbLogBegin();

    HbLogEnd();
}

void UserMainWindow::onStartClicked()
{
    HbLogBegin();

    HbTcpClientConfig config;
    config.setAddress( QHostAddress::LocalHost );
    config.setPort( 4000 );
    config.setReconnectionDelay( 0 );
    config.setBadHeaderTolerant( false );

    networkuid server_uid = mpHbClient->joinTcpClient( config, true );
    if( server_uid > 0 )
    {
        HbInfo( "Client %d started.", server_uid );
    }

    HbLogEnd();
}

void UserMainWindow::onStopClicked()
{
    mpHbClient->leave();
}

void UserMainWindow::onUserConnectionRequest()
{
    HbLogBegin();

    HbWarning( "TODO" );

    HbLogEnd();
}

void UserMainWindow::onFacebookConnectionRequest()
{
    HbLogBegin();

    mpHbClient->facebookAuthRequested();

    HbLogEnd();
}

void UserMainWindow::onClientStatusChanged( networkuid client_uid, HbNetworkProtocol::ClientStatus status )
{
    HbInfo( "Status changed on client %d: %s.", client_uid, HbLatin1( HbNetworkProtocol::MetaClientStatus::toString( status ) ) );
}

void UserMainWindow::onMeStatusChanged( HbNetworkProtocol::UserStatus status )
{
    HbInfo( "My status changed: %s.", HbLatin1( HbNetworkProtocol::MetaUserStatus::toString( status ) ) );
}
