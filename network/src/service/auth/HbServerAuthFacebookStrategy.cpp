// Hb
#include <HbLogService.h>
#include <facebook/HbO2ServerFacebook.h>
#include <facebook/api/HbFacebookUser.h>
// Local
#include <service/auth/HbAuthService.h>
#include <service/auth/HbServerAuthFacebookStrategy.h>
#include <contract/auth/HbAuthFacebookRequestContract.h>

using namespace hb::network;
using namespace hb::link;

HbServerAuthFacebookStrategy::HbServerAuthFacebookStrategy() :
    HbServerAuthStrategy()
{
    connect( &mRequester, &HbFacebookRequester::requestCompleted, this, &HbServerAuthFacebookStrategy::onRequestCompleted, Qt::UniqueConnection );
}

void HbServerAuthFacebookStrategy::reset()
{
    mPendingToken.clear();
    mPendingRequest.clear();
}

void HbServerAuthFacebookStrategy::setConfig( const HbO2ServerConfig & config )
{
    mConfig = config;
}

authstgy HbServerAuthFacebookStrategy::type() const
{
    return HbAuthService::AUTH_FACEBOOK;
}

bool HbServerAuthFacebookStrategy::checkLogin( const HbAuthRequestContract * contract )
{
    const HbAuthFacebookRequestContract * facebook_auth = contract->value< HbAuthFacebookRequestContract >();

    if( !facebook_auth )
    {
        return false;
    }

    HbO2ServerFacebook * server_auth = new HbO2ServerFacebook();

    connect( server_auth, &HbO2ServerFacebook::linkSucceed, this, &HbServerAuthFacebookStrategy::onLinkSucceed, Qt::UniqueConnection );
    connect( server_auth, &HbO2ServerFacebook::linkFailed,  this, &HbServerAuthFacebookStrategy::onLinkFailed,  Qt::UniqueConnection );

    server_auth->config().setClientId    ( mConfig.clientId() );
    server_auth->config().setClientSecret( mConfig.clientSecret() );
    server_auth->setRedirectUri        ( facebook_auth->client().redirectUri() );
    server_auth->setCode               ( facebook_auth->client().code() );

    mPendingToken.insert( server_auth, contract->sender() );

    server_auth->link();

    return true;

}

// Problem: onLinkSucceed and onLinkFailed are both called. That causes problems
// as deleterLater is called in each of them.

void HbServerAuthFacebookStrategy::onLinkSucceed()
{
    HbLogBegin();
    HbO2ServerFacebook * server_auth = dynamic_cast< HbO2ServerFacebook * >( sender() );
    q_assert_ptr( server_auth );
    q_assert( mPendingToken.contains( server_auth ) );

    HbInfo( "Server link succeed. Requesting Facebook user object %s...", HbLatin1( server_auth->config().clientId() ) );

    networkuid sender = mPendingToken.take( server_auth );
    quint64 request_id = mRequester.requestUser( server_auth );
    if( request_id > 0 )
    {
        mPendingRequest.insert( request_id, sender );
    }
    else
    {
        emit authFailed( sender, HbNetworkProtocol::AUTH_INTERNAL_ERROR, "" );
    }

    server_auth->deleteLater();

    HbLogEnd();
}

void HbServerAuthFacebookStrategy::onLinkFailed(const QString & error )
{
    HbLogBegin();
    HbO2ServerFacebook * server_auth = dynamic_cast< HbO2ServerFacebook * >( sender() );
    q_assert_ptr( server_auth );
    q_assert( mPendingToken.contains( server_auth ) );

    HbInfo( "Server link failed for user %s ( %s ).", HbLatin1( server_auth->config().clientId() ), HbLatin1( error ) );

    networkuid sender = mPendingToken.take( server_auth );

    server_auth->deleteLater();

    emit authFailed( sender, HbNetworkProtocol::AUTH_FB_KO, error );
    HbLogEnd();
}

void HbServerAuthFacebookStrategy::onRequestCompleted( quint64 request_id, HbFacebookObject * object )
{
    q_assert( mPendingRequest.contains( request_id ) );

    networkuid sender = mPendingRequest.take( request_id );

    HbFacebookUser * user = dynamic_cast< HbFacebookUser * >( object );
    if( user )
    {
        HbInfo( "Facebook user informations: %s", HbLatin1( user->toString() ) );

        HbNetworkUserInfo user_info;
        user_info.setId       ( user->id() );
        user_info.setType     ( HbAuthService::AUTH_FACEBOOK );
        user_info.setEmail    ( user->email() );
        user_info.setNickname ( user->firstName() + " " +
                                user->lastName() );
        user_info.setFirstName( user->firstName() );
        user_info.setLastName ( user->lastName() );
        if( user->gender() == "male" )
        {
            user_info.setGender( HbNetworkUserInfo::GENDER_MALE );
        }
        else if( user->gender() == "female" )
        {
            user_info.setGender( HbNetworkUserInfo::GENDER_FEMALE );
        }

        emit authSucceed( sender, user_info );
    }
    else
    {
        HbError( "Bad dynamic cast HbFacebookObject -> HbFacebookUser." );
        emit authFailed( sender, HbNetworkProtocol::AUTH_FB_KO, "" );
    }

    if( object )
    {
        delete object;
    }
}
