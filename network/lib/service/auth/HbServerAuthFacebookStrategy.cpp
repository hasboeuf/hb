// Hb
#include <HbLogService.h>
#include <facebook/HbO2ServerFacebook.h>
#include <facebook/api/HbFacebookUser.h>
// Local
#include <service/auth/HbAuthService.h>
#include <service/auth/HbServerAuthFacebookStrategy.h>
#include <contract/auth/HbOAuthRequestContract.h>
#ifdef DEV
#include <mock/HbNetworkUserInfoMock.h>
#endif

using namespace hb::network;
using namespace hb::link;

HbServerAuthFacebookStrategy::HbServerAuthFacebookStrategy() :
    HbServerOAuthStrategy()
{
    connect( &mRequester, &HbFacebookRequester::requestCompleted, this, &HbServerAuthFacebookStrategy::onRequestCompleted, Qt::UniqueConnection );
}

authstgy HbServerAuthFacebookStrategy::type() const
{
    return HbAuthService::AUTH_FACEBOOK;
}

bool HbServerAuthFacebookStrategy::checkLogin( const HbAuthRequestContract * contract )
{
    const HbOAuthRequestContract * facebook_auth = contract->value< HbOAuthRequestContract >();

    if( !facebook_auth )
    {
        return false;
    }

    HbO2ServerFacebook * server_auth = new HbO2ServerFacebook();

    connect( server_auth, &HbO2ServerFacebook::linkSucceed, this, &HbServerAuthFacebookStrategy::onLinkSucceed, Qt::UniqueConnection );
    connect( server_auth, &HbO2ServerFacebook::linkFailed,  this, &HbServerOAuthStrategy::onLinkFailed,  Qt::UniqueConnection );

    server_auth->config().setClientId( mConfig.clientId() );
    server_auth->config().setClientSecret( mConfig.clientSecret() );
    server_auth->setRedirectUri( facebook_auth->redirectUri() );
    server_auth->setCode       ( facebook_auth->code() );
    server_auth->addField( FB_USER_FIRST_NAME );
    server_auth->addField( FB_USER_LAST_NAME );
    server_auth->addField( FB_USER_LINK );
    server_auth->addField( FB_USER_EMAIL );
    server_auth->addField( FB_USER_GENDER );
    server_auth->addField( FB_USER_LOCALE );
    server_auth->addField( FB_USER_VERIFIED );
    server_auth->addField( FB_USER_TIMEZONE );

    mPendingToken.insert( server_auth, contract->sender() );

    server_auth->link();

    return true;

}

// Problem: onLinkSucceed and onLinkFailed are both called. That causes problems
// as deleterLater is called in each of them.

void HbServerAuthFacebookStrategy::onLinkSucceed()
{
    HbO2ServerFacebook * server_auth = dynamic_cast< HbO2ServerFacebook * >( sender() );
    q_assert_ptr( server_auth );
    q_assert( mPendingToken.contains( server_auth ) );

    qDebug() << "Server link succeed. Requesting Facebook user object" << server_auth->config().clientId();

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
}

void HbServerAuthFacebookStrategy::onRequestCompleted( quint64 request_id, HbFacebookObject * object )
{
    q_assert( mPendingRequest.contains( request_id ) );

    networkuid sender = mPendingRequest.take( request_id );

    HbFacebookUser * user = dynamic_cast< HbFacebookUser * >( object );
    if( user )
    {
        qDebug() << "Facebook user informations:" << user->toString();

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

#ifdef DEV
        HbNetworkUserInfoMock::mockNetworkUserInfo( user_info ); // Randomize user.
#endif

        emit authSucceed( sender, user_info );
    }
    else
    {
        qWarning() << "Bad dynamic cast HbFacebookObject -> HbFacebookUser";
        emit authFailed( sender, HbNetworkProtocol::AUTH_OAUTH_KO, "" );
    }

    if( object )
    {
        delete object;
    }
}
