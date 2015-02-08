// Qt
#include <QtCore/QUrl>
#include <QtGui/QDesktopServices>
#include <QtNetwork/QNetworkReply>
// Hb
#include <HbLogService.h>
#include <client/HbO2ClientFacebook.h>
#include <server/HbO2ServerFacebook.h>
// Local
#include <LinkMainWindow.h>


using namespace hb::link;
using namespace hb::linkexample;

LinkMainWindow::LinkMainWindow(QWidget * parent) :
    QMainWindow( parent )
{

    HbLogBegin();

    // Ui
    setupUi( this );
    setWindowTitle( "Link" );

    mpFacebookClient = nullptr;
    mpFacebookServer = nullptr;

    connect( ui_qpb_connect, &QPushButton::clicked, this, &LinkMainWindow::onConnectClicked );
    connect( &mNetworkAccess, &QNetworkAccessManager::finished, this, &LinkMainWindow::onNetworkAccessFinished );

    HbLogEnd();
}

LinkMainWindow::~LinkMainWindow()
{
    HbLogBegin();

    if( mpFacebookClient )
    {
        delete mpFacebookClient;
    }

    HbLogEnd();
}

void LinkMainWindow::onConnectClicked()
{
    HbLogBegin();

    mpFacebookClient = new HbO2ClientFacebook();

    connect( mpFacebookClient, &HbO2Client::openBrowser, this, &LinkMainWindow::onOpenBrower );
    connect( mpFacebookClient, &HbO2::linkingSucceed, this, &LinkMainWindow::onClientLinkSucceed );

    mpFacebookClient->setClientId( "940633959281250" );
    mpFacebookClient->setLocalPort( 8080 );
    mpFacebookClient->addScope( FB_PERMISSION_EMAIL );
    mpFacebookClient->addScope( FB_PERMISSION_FRIENDS );
    mpFacebookClient->link();

    HbLogEnd();

}

void LinkMainWindow::onNetworkAccessFinished( QNetworkReply * reply )
{
    HbLogBegin();

    if( reply->error() == QNetworkReply::NoError )
    {
        HbInfo( "Reply succeed." );

        QByteArray raw = reply->readAll();
        QString content( raw );

        HbInfo( "Reply content: %s", HbLatin1( content ) );
    }
    else
    {
        HbError( "Reply error: %s", HbLatin1( reply->errorString() ) );
    }

    reply->deleteLater();

    HbLogEnd();
}

void LinkMainWindow::onOpenBrower( const QUrl & url )
{
    HbInfo( "Opening browser on %s", HbLatin1( url.toString() ) );
    QDesktopServices::openUrl( url );
}

void LinkMainWindow::onClientLinkSucceed()
{
    if( sender() != mpFacebookClient )
    {
        return;
    }

    HbInfo( "Client link succeed" );

    mpFacebookServer = new HbO2ServerFacebook();

    connect( mpFacebookServer, &HbO2ServerFacebook::linkingSucceed, this, &LinkMainWindow::onServerLinkSucceed );

    mpFacebookServer->setClientId( mpFacebookClient->clientId() );
    mpFacebookServer->setRedirectUri( mpFacebookClient->redirectUri() );
    mpFacebookServer->setCode( mpFacebookClient->code() );
    mpFacebookServer->setClientSecret( "74621eedf9aa2cde9cd31dc5c4d3c440" );

    mpFacebookClient->deleteLater();
    mpFacebookClient = nullptr;

    mpFacebookServer->link();
}

void LinkMainWindow::onServerLinkSucceed()
{
    if( sender() != mpFacebookServer )
    {
        return;
    }

    HbInfo( "Server link succeed" );

}

