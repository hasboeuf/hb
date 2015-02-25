// Qt
#include <QtGui/QDesktopServices>
// Hb
#include <HbLogService.h>
#include <facebook/HbO2ServerFacebook.h>
#include <facebook/api/HbFacebookUser.h>
// Local
#include <service/auth/HbAuthService.h>
#include <service/auth/HbClientAuthLoginObject.h>
#include <service/auth/HbClientAuthFacebookStrategy.h>
#include <contract/auth/HbAuthFacebookRequestContract.h>

using namespace hb::network;
using namespace hb::link;

authstgy HbClientAuthFacebookStrategy::type() const
{
    return HbAuthService::AUTH_FACEBOOK;
}

bool HbClientAuthFacebookStrategy::prepareAuthContract( HbClientAuthLoginObject * login_object )
{
    HbO2ClientFacebook * facebook_client = new HbO2ClientFacebook();

    connect( facebook_client, &HbO2Client::openBrowser,
             this, &HbClientAuthFacebookStrategy::onFacebookOpenBrower );
    connect( facebook_client, &HbO2::linkSucceed,
             this, &HbClientAuthFacebookStrategy::onFacebookLinkSucceed );
    connect( facebook_client, &HbO2::linkFailed,
             this, &HbClientAuthFacebookStrategy::onFacebookLinkFailed );

    facebook_client->setClientId( "940633959281250" ); // TODO config
    facebook_client->setLocalPort( 8080 );
    facebook_client->addScope( FB_PERMISSION_EMAIL );
    facebook_client->addScope( FB_PERMISSION_FRIENDS );

    mPendingCodes.insert( facebook_client, login_object->socketUid() );

    facebook_client->link();
}

void HbClientAuthFacebookStrategy::onFacebookOpenBrower( const QUrl & url )
{
    HbInfo( "Opening browser on %s", HbLatin1( url.toString() ) );
    QDesktopServices::openUrl( url );
}

void HbClientAuthFacebookStrategy::onFacebookLinkSucceed()
{
    HbO2ClientFacebook * facebook_client = dynamic_cast< HbO2ClientFacebook * >( sender() );
    q_assert_ptr( facebook_client );
    q_assert( mPendingCodes.contains( facebook_client ) );

    networkuid socket_uid = mPendingCodes.value( facebook_client );

    HbAuthFacebookRequestContract * contract = new HbAuthFacebookRequestContract();
    contract->setType( HbAuthService::AUTH_FACEBOOK );
    contract->setClient( *facebook_client );

    mPendingCodes.remove( facebook_client );
    facebook_client->deleteLater();

    emit authContractReady( socket_uid, contract );
}

void HbClientAuthFacebookStrategy::onFacebookLinkFailed()
{
    HbO2ClientFacebook * facebook_client = dynamic_cast< HbO2ClientFacebook * >( sender() );
    q_assert_ptr( facebook_client );
    q_assert( mPendingCodes.contains( facebook_client ) );

    networkuid socket_uid = mPendingCodes.value( facebook_client );

    mPendingCodes.remove( facebook_client );
    facebook_client->deleteLater();

    emit authContractFailed( socket_uid, "Facebook link failed." );
}


