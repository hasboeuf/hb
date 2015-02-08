// Qt
#include <QtCore/QUrl>
#include <QtCore/QUrlQuery>
#include <QtGui/QDesktopServices>
#include <QtNetwork/QNetworkReply>
// Hb
#include <HbLogService.h>
#include <core/HbDictionaryHelper.h>
#include <facebook/HbO2ClientFacebook.h>
#include <facebook/HbO2ServerFacebook.h>
#include <facebook/api/HbFacebookUser.h>
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

    connect( &mRequester, &HbFacebookRequester::requestCompleted, this, &LinkMainWindow::onRequestCompleted );

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

    connect( mpFacebookServer, &HbO2ServerFacebook::linkingSucceed, this, &LinkMainWindow::onServerLinkSucceed, Qt::UniqueConnection );

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

    HbInfo( "Server link succeed. Request facebook user..." );

    mRequester.requestUser( mpFacebookServer );
}

void LinkMainWindow::onRequestCompleted( hb::link::HbFacebookObject * object )
{
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
