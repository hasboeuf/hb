// Qt
// Hb
#include <HbLogService.h>
#include <facebook/HbO2ClientFacebook.h>
// Local
#include <service/auth/HbClientAuthService.h>
#include <service/auth/HbClientAuthLoginObject.h>
#include <service/auth/HbClientAuthFacebookStrategy.h>
#include <contract/auth/HbAuthFacebookRequestContract.h>

using namespace hb::network;

HbClientAuthService::HbClientAuthService()
{
    HbClientAuthFacebookStrategy * fb_strategy = new HbClientAuthFacebookStrategy();
    mStrategies.insert( fb_strategy->type(), fb_strategy );

    foreach( HbClientAuthStrategy * strategy, mStrategies )
    {
        if( strategy )
        {
            connect( strategy, &HbAuthStrategy::loginFailed,
                     this,     &HbClientAuthService::onLoginFailed, Qt::UniqueConnection );
            connect( strategy, &HbAuthStrategy::loginSucceed,
                     this,     &HbClientAuthService::onLoginSucceed, Qt::UniqueConnection );
        }
    }
}

const HbServiceAuthClientConfig & HbClientAuthService::config() const
{
    return mConfig;
}

void HbClientAuthService::setConfig( const HbServiceAuthClientConfig & config )
{
    if( config.isValid() )
    {
        mConfig = config;
    }
}

void HbClientAuthService::onContractReceived( const HbNetworkContract * contract )
{

}

void HbClientAuthService::onSocketConnected( networkuid )
{
    // Unused.
}

void HbClientAuthService::onSocketDisconnected( networkuid socket_uid )
{

}

void HbClientAuthService::onAuthRequest( HbClientAuthLoginObject * login_object )
{
    q_assert_ptr( login_object );
    q_assert( mPendingSocket == 0 );

    authstgy strategy_id = login_object->strategy();

    HbClientAuthStrategy * strategy = mStrategies.value( strategy_id, nullptr );
    if( strategy )
    {
        if( strategy->tryLogin( login_object ) )
        {
            mPendingSocket = login_object->socketUid();
        }
        else
        {
            HbError( "Fail trying to log." );
        }
    }
    else
    {
        HbError( "No user auth strategy defined." );
    }

    delete login_object;
}

void HbClientAuthService::onLoginSucceed( networkuid socket_uid, const HbNetworkUserInfo & user_info )
{
    mPendingSocket = 0;
    /*if( checkSocket( socket_uid ) )
    {
        HbAuthStatusContract * response = mResponses.value( socket_uid, nullptr );
        if( !response )
        {
            kickSocket( socket_uid, HbNetworkProtocol::KICK_INTERNAL_ERROR );
            return;
        }

        emit userAuthenticated( socket_uid, user_info );

        response->setStatus( HbNetworkProtocol::AUTH_OK );
        response->setTryNumber( 1 ); // TODO store try number.
        response->setMaxTries( mConfig.authMaxTries() );

        delSocket( socket_uid, false );

        // TODO emit contract.
    }
    else
    {
        HbWarning( "Socket %d disconnected before getting ok auth response.", socket_uid );
    }*/
}

void HbClientAuthService::onLoginFailed( networkuid socket_uid, HbNetworkProtocol::AuthStatus status, const QString & description )
{
    mPendingSocket = 0;
    /*if( checkSocket( socket_uid ) )
    {
        HbAuthStatusContract * response = mResponses.value( socket_uid, nullptr );
        if( !response )
        {
            kickSocket( socket_uid, HbNetworkProtocol::KICK_INTERNAL_ERROR );
            return;
        }

        if( 0 ) // Max tries.
        {
            kickSocket( socket_uid, HbNetworkProtocol::KICK_AUTH_LIMIT );
        }

        response->setStatus( status );
        response->setDescription( description );
        response->setTryNumber( 1 ); // TODO store try number.
        response->setMaxTries( mConfig.authMaxTries() );

        // TODO emit contract.
    }
    else
    {
        HbWarning( "Socket %d disconnected before getting nok auth response.", socket_uid );
    }*/
}
