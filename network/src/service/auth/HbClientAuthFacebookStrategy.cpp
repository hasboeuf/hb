// Hb
#include <HbLogService.h>
#include <facebook/HbO2ServerFacebook.h>
#include <facebook/api/HbFacebookUser.h>
// Local
#include <service/auth/HbAuthService.h>
#include <service/auth/HbClientAuthFacebookStrategy.h>
#include <contract/auth/HbAuthFacebookRequestContract.h>

using namespace hb::network;
using namespace hb::link;

bool HbClientAuthFacebookStrategy::tryLogin( HbClientAuthLoginObject * )
{
    /*const HbAuthFacebookRequestContract * facebook_auth = contract->value< HbAuthFacebookRequestContract >();

    if( !facebook_auth )
    {
        return false;
    }

    HbO2ServerFacebook * server_auth = new HbO2ServerFacebook();

    connect( server_auth, &HbO2ServerFacebook::linkSucceed, this, &HbServerAuthFacebookStrategy::onLinkSucceed, Qt::UniqueConnection );
    connect( server_auth, &HbO2ServerFacebook::linkFailed,  this, &HbServerAuthFacebookStrategy::onLinkFailed,  Qt::UniqueConnection );

    server_auth->setClientId    ( facebook_auth->client().clientId() );
    server_auth->setRedirectUri ( facebook_auth->client().redirectUri() );
    server_auth->setCode        ( facebook_auth->client().code() );
    server_auth->setClientSecret( "74621eedf9aa2cde9cd31dc5c4d3c440" ); // TODO in config.

    mPendingToken.insert( server_auth, contract->sender() );

    server_auth->link();

    return true;*/

}

authstgy HbClientAuthFacebookStrategy::type() const
{
    return HbAuthService::AUTH_FACEBOOK;
}

void HbClientAuthFacebookStrategy::onFacebookOpenBrower( const QUrl & url )
{

}

void HbClientAuthFacebookStrategy::onFacebookLinked()
{

}


