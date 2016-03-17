// Qt
#include <QtCore/QUrl>
#include <QtCore/QUrlQuery>
#include <QtGui/QDesktopServices>
#include <QtNetwork/QNetworkReply>
// Hb
#include <HbLogService.h>
#include <HbLoggerOutputs.h>
#include <core/HbDictionaryHelper.h>
#include <facebook/HbO2ClientFacebook.h>
#include <facebook/HbO2ServerFacebook.h>
#include <facebook/api/HbFacebookUser.h>
#include <google/HbO2ClientGoogle.h>
#include <google/HbO2ServerGoogle.h>
#include <google/api/HbGoogleUser.h>
// Local
#include <LinkMainWindow.h>

using namespace hb::log;
using namespace hb::link;
using namespace hb::linkexample;

QString LinkMainWindow::msClientId     = "940633959281250";                  // Fake value.
QString LinkMainWindow::msClientSecret = "74621eedf9aa2cde9cd31dc5c4d3c440"; // Fake value.

LinkMainWindow::LinkMainWindow(QWidget * parent) :
    QMainWindow( parent )
{

    // Log
    QString error;
    if( HbLogService::outputs()->addConsoleOutput( &error ) == 0 )
    {
        printf( "HbLog error: %s", HbLatin1( error ) );
    }

    HbLogBegin();

    // Ui
    setupUi( this );
    setWindowTitle( "Link" );

    mpFacebookClient = nullptr;
    mpFacebookServer = nullptr;
    mpGoogleClient   = nullptr;
    mpGoogleServer   = nullptr;

    connect( ui_qpb_facebook_connect, &QPushButton::clicked, this, &LinkMainWindow::onFacebookConnectClicked );
    connect( ui_qpb_google_connect,   &QPushButton::clicked, this, &LinkMainWindow::onGoogleConnectClicked );

    connect( &mFacebookRequester, &HbFacebookRequester::requestCompleted, this, &LinkMainWindow::onFacebookRequestCompleted );
    connect( &mGoogleRequester,   &HbGoogleRequester::requestCompleted, this, &LinkMainWindow::onGoogleRequestCompleted );

    HbLogEnd();
}

LinkMainWindow::~LinkMainWindow()
{
    HbLogBegin();

    if( mpFacebookClient ) delete mpFacebookClient;
    if( mpFacebookServer ) delete mpFacebookServer;
    if( mpGoogleClient   ) delete mpGoogleClient;
    if( mpGoogleServer   ) delete mpGoogleServer;

    HbLogEnd();
}

void LinkMainWindow::onFacebookConnectClicked()
{
    HbLogBegin();

    mpFacebookClient = new HbO2ClientFacebook();

    connect( mpFacebookClient, &HbO2Client::openBrowser, this, &LinkMainWindow::onOpenBrower );
    connect( mpFacebookClient, &HbO2::linkSucceed, this, &LinkMainWindow::onFacebookClientLinkSucceed );

    mpFacebookClient->config().setClientId( msClientId );
    mpFacebookClient->config().setLocalPort( 8080 );
    mpFacebookClient->config().addScope( FB_PERMISSION_EMAIL );
    mpFacebookClient->config().addScope( FB_PERMISSION_FRIENDS );

    mpFacebookClient->link();

    HbLogEnd();

}

void LinkMainWindow::onGoogleConnectClicked()
{
    HbLogBegin();

    mpGoogleClient = new HbO2ClientGoogle();

    connect( mpGoogleClient, &HbO2Client::openBrowser, this, &LinkMainWindow::onOpenBrower );
    connect( mpGoogleClient, &HbO2::linkSucceed, this, &LinkMainWindow::onGoogleClientLinkSucceed );

    mpGoogleClient->config().setClientId( msClientId );
    mpGoogleClient->config().setLocalPort( 8080 );
    mpGoogleClient->config().addScope( GL_PERMISSION_EMAIL );
    mpGoogleClient->config().addScope( GL_PERMISSION_PROFILE );

    mpGoogleClient->link();

    HbLogEnd();

}

void LinkMainWindow::onOpenBrower( const QUrl & url )
{
    HbInfo( "Opening browser on %s", HbLatin1( url.toString() ) );
    QDesktopServices::openUrl( url );
}

void LinkMainWindow::onFacebookClientLinkSucceed()
{
    if( sender() != mpFacebookClient )
    {
        return;
    }

    HbInfo( "Client link succeed" );

    mpFacebookServer = new HbO2ServerFacebook();

    connect( mpFacebookServer, &HbO2ServerFacebook::linkSucceed, this, &LinkMainWindow::onFacebookServerLinkSucceed, Qt::UniqueConnection );

    mpFacebookServer->config().setClientId( mpFacebookClient->config().clientId() );
    mpFacebookServer->config().setClientSecret( msClientSecret );
    mpFacebookServer->setRedirectUri( mpFacebookClient->redirectUri() );
    mpFacebookServer->setCode( mpFacebookClient->code() );
    mpFacebookServer->addField( FB_USER_FIRST_NAME );
    mpFacebookServer->addField( FB_USER_LAST_NAME );
    mpFacebookServer->addField( FB_USER_LINK );
    mpFacebookServer->addField( FB_USER_EMAIL );
    mpFacebookServer->addField( FB_USER_GENDER );
    mpFacebookServer->addField( FB_USER_LOCALE );
    mpFacebookServer->addField( FB_USER_VERIFIED );
    mpFacebookServer->addField( FB_USER_TIMEZONE );

    mpFacebookClient->deleteLater();
    mpFacebookClient = nullptr;

    mpFacebookServer->link();
}

void LinkMainWindow::onFacebookServerLinkSucceed()
{
    if( sender() != mpFacebookServer )
    {
        return;
    }

    HbInfo( "Server link succeed. Request facebook user..." );

    quint64 request_id = mFacebookRequester.requestUser( mpFacebookServer );
    if( request_id > 0 )
    {
        HbInfo( "Request id: %lld.", request_id );
    }
    else
    {
        HbError( "Request user failed." );
    }

    mpFacebookServer->deleteLater();
    mpFacebookServer = nullptr;
}

void LinkMainWindow::onFacebookRequestCompleted( quint64 request_id, hb::link::HbFacebookObject * object )
{
    HbInfo( "Request %lld completed.", request_id );
    if( !object )
    {
        HbError( "Facebook object null." );
        return;
    }

    HbInfo( "Facebook object of type %s received.",
            HbLatin1( HbFacebookObject::MetaObjectType::toString( object->type() ) ) );

    if( object->type() == HbFacebookObject::OBJECT_USER )
    {
        HbFacebookUser * user = dynamic_cast< HbFacebookUser * >( object );
        if( user )
        {
            HbInfo( "Facebook user informations: %s", HbLatin1( user->toString() ) );
        }
        else
        {
            HbError( "Bad dynamic cast HbFacebookObject -> HbFacebookUser." );
        }
    }
    else
    {
        HbWarning( "No displayable for this type." );
    }

    delete object;
}

void LinkMainWindow::onGoogleClientLinkSucceed()
{
    if( sender() != mpGoogleClient )
    {
        return;
    }

    HbInfo( "Client link succeed" );

    mpGoogleServer = new HbO2ServerGoogle();

    connect( mpGoogleServer, &HbO2ServerGoogle::linkSucceed, this, &LinkMainWindow::onGoogleServerLinkSucceed, Qt::UniqueConnection );

    mpGoogleServer->config().setClientId( mpGoogleClient->config().clientId() );
    mpGoogleServer->config().setClientSecret( msClientSecret );
    mpGoogleServer->setRedirectUri( mpGoogleClient->redirectUri() );
    mpGoogleServer->setCode( mpGoogleClient->code() );

    mpGoogleClient->deleteLater();
    mpGoogleClient = nullptr;

    mpGoogleServer->link();
}

void LinkMainWindow::onGoogleServerLinkSucceed()
{
    if( sender() != mpGoogleServer )
    {
        return;
    }

    HbInfo( "Server link succeed. Request google user..." );

    quint64 request_id = mGoogleRequester.requestUser( mpGoogleServer );
    if( request_id > 0 )
    {
        HbInfo( "Request id: %lld.", request_id );
    }
    else
    {
        HbError( "Request user failed." );
    }

    mpGoogleServer->deleteLater();
    mpGoogleServer = nullptr;
}

void LinkMainWindow::onGoogleRequestCompleted( quint64 request_id, hb::link::HbGoogleObject * object )
{
    HbInfo( "Request %lld completed.", request_id );
    if( !object )
    {
        HbError( "Google object null." );
        return;
    }

    HbInfo( "Google object of type %s received.",
            HbLatin1( HbGoogleObject::MetaObjectType::toString( object->type() ) ) );

    if( object->type() == HbGoogleObject::OBJECT_USER )
    {
        HbGoogleUser * user = dynamic_cast< HbGoogleUser * >( object );
        if( user )
        {
            HbInfo( "Google user informations: %s", HbLatin1( user->toString() ) );
        }
        else
        {
            HbError( "Bad dynamic cast HbGoogleObject -> HbGoogleUser." );
        }
    }
    else
    {
        HbWarning( "No displayable for this type." );
    }

    delete object;
}
