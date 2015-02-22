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
using namespace hb::network;
using namespace hb::networkexample;

UserMainWindow::UserMainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    // Log
    /*QString error;
    if( HbLogService::outputs()->addConsoleOutput( &error ) == 0 )
    {
        qDebug() << "HbLog error: " << error;
    }*/

    HbLogBegin();

    // Ui
    setupUi( this );
    setWindowTitle( "User" );

    HbGeneralClientConfig config;
    config.setAppName( "hb-network-example" );
    config.setProtocolVersion( 1 );
    config.presence().setKeepAliveInterval( 1 );

    mpHbClient       = new HbClient( config );
    mpFacebookClient = nullptr;

    connect( ui_qpb_start,           &QPushButton::clicked, this, &UserMainWindow::onStartClicked );
    connect( ui_qpb_stop,            &QPushButton::clicked, this, &UserMainWindow::onStopClicked );
    connect( ui_qpb_user_connection, &QPushButton::clicked, this, &UserMainWindow::onUserConnectionRequest );
    connect( ui_qpb_fb_connection,   &QPushButton::clicked, this, &UserMainWindow::onFacebookConnectionRequest );

    HbLogEnd();
}

UserMainWindow::~UserMainWindow()
{
    HbLogBegin();

    if( mpFacebookClient ) delete mpFacebookClient;

    HbLogEnd();
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

    HbTcpClientConfig config;
    config.setAddress( QHostAddress::LocalHost );
    config.setPort( 4000 );
    config.setReconnectionDelay( 1000 );

    quint16 server_uid = mpHbClient->joinTcpClient( config, true );
    if( server_uid > 0 )
    {
        HbInfo( "Client #%d started.", server_uid );
    }

    HbLogEnd();
}

void UserMainWindow::onStopClicked()
{

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

    if( !mpFacebookClient )
    {
        mpFacebookClient = new HbO2ClientFacebook();

        connect( mpFacebookClient, &HbO2Client::openBrowser, this, &UserMainWindow::onFacebookOpenBrower );
        connect( mpFacebookClient, &HbO2::linkSucceed,       this, &UserMainWindow::onFacebookLinked );
    }

    if( mpFacebookClient->linkStatus() == HbO2Client::UNLINKED )
    {
        mpFacebookClient->setClientId( "940633959281250" );
        mpFacebookClient->setLocalPort( 8080 );
        mpFacebookClient->addScope( FB_PERMISSION_EMAIL );
        mpFacebookClient->addScope( FB_PERMISSION_FRIENDS );
        mpFacebookClient->link();
    }
    else
    {
        HbWarning( "Facebook client already linked or linking." );
    }

    HbLogEnd();
}

void UserMainWindow::onFacebookOpenBrower( const QUrl & url )
{
    HbInfo( "Opening browser on %s", HbLatin1( url.toString() ) );
    QDesktopServices::openUrl( url );
}

void UserMainWindow::onFacebookLinked()
{
    if( sender() != mpFacebookClient )
    {
        return;
    }

    HbAuthFacebookRequestContract * contract = new HbAuthFacebookRequestContract();
    contract->setClient( *mpFacebookClient );
}
