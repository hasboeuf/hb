// Qt
// Hb
#include <HbLogService.h>
#include <facebook/HbO2ClientFacebook.h>
// Local
#include <service/auth/HbClientAuthService.h>
#include <service/auth/HbClientAuthLoginObject.h>
#include <service/auth/HbClientAuthFacebookStrategy.h>
#include <contract/auth/HbAuthFacebookRequestContract.h>
#include <contract/auth/HbAuthStatusContract.h>

using namespace hb::network;

HbClientAuthService::HbClientAuthService()
{
    HbClientAuthFacebookStrategy * fb_strategy = new HbClientAuthFacebookStrategy();
    mStrategies.insert( fb_strategy->type(), fb_strategy );

    foreach( HbClientAuthStrategy * strategy, mStrategies )
    {
        if( strategy )
        {
            connect( strategy, &HbClientAuthStrategy::authContractReady,
                     this,     &HbClientAuthService::onAuthContractReady, Qt::UniqueConnection );
            connect( strategy, &HbClientAuthStrategy::authContractFailed,
                     this,     &HbClientAuthService::onAuthContractFailed, Qt::UniqueConnection );
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
    q_assert_ptr( contract );

    const HbAuthStatusContract * auth_status = contract->value< HbAuthStatusContract >();
    if( auth_status )
    {
        networkuid sender = auth_status->sender();
        HbNetworkProtocol::AuthStatus status = auth_status->status();

        if( status == HbNetworkProtocol::AUTH_OK )
        {
            // emit socketAuthenticated( sender, user_info );
            return;
        }

        quint8 try_number = auth_status->tryNumber(); // TODO
        quint8 max_tries  = auth_status->maxTries(); // TODO
        QString error     = auth_status->description();

        emit socketUnauthenticated( sender, error );

    }
    else
    {
        HbError( "Auth contract type not recognized." );
    }

    delete contract;
}

void HbClientAuthService::onSocketConnected( networkuid )
{
    // Unused.
}

void HbClientAuthService::onSocketDisconnected( networkuid socket_uid )
{
    if( socket_uid == mPendingSocket )
    {
        HbInfo( "Socket %d disconnected an auth request is pending.", socket_uid );
        mPendingSocket = 0;
    }
}

void HbClientAuthService::onAuthRequested( HbClientAuthLoginObject * login_object )
{
    q_assert_ptr( login_object );
    q_assert( mPendingSocket == 0 );

    authstgy strategy_id = login_object->strategy();

    HbClientAuthStrategy * strategy = mStrategies.value( strategy_id, nullptr );
    if( strategy )
    {
        if( strategy->prepareAuthContract( login_object ) )
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

void HbClientAuthService::onAuthContractReady( networkuid socket_uid, const HbAuthRequestContract * contract )
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

void HbClientAuthService::onAuthContractFailed( networkuid socket_uid, const QString & description )
{
    mPendingSocket = 0;

    emit socketUnauthenticated( socket_uid, description );
}
