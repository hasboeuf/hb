// Qt
// Hb
#include <HbLogService.h>
#include <facebook/HbO2ClientFacebook.h>
// Local
#include <service/auth/HbClientAuthService.h>
#include <service/auth/HbClientAuthLoginObject.h>
#include <service/auth/HbClientAuthStrategy.h>
#include <contract/auth/HbAuthRequestContract.h>
#include <contract/auth/HbAuthStatusContract.h>

using namespace hb::network;

HbClientAuthService::HbClientAuthService()
{
    mPendingSocket = 0;
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

void HbClientAuthService::addStrategy( HbClientAuthStrategy * strategy )
{
    if( strategy && !mStrategies.contains( strategy->type() ) )
    {
        connect( strategy, &HbClientAuthStrategy::authContractReady,
                 this,     &HbClientAuthService::onAuthContractReady, Qt::UniqueConnection );
        connect( strategy, &HbClientAuthStrategy::authContractFailed,
                 this,     &HbClientAuthService::onAuthContractFailed, Qt::UniqueConnection );

        mStrategies.insert( strategy->type(), strategy );
    }
    else
    {
        HbWarning( "Strategy already defined or null." );
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

void HbClientAuthService::onAuthContractReady( networkuid socket_uid, HbAuthRequestContract * contract )
{
    mPendingSocket = 0;
    contract->addSocketReceiver( socket_uid );
    emit readyContractToSend( contract );
}

void HbClientAuthService::onAuthContractFailed( networkuid socket_uid, const QString & description )
{
    mPendingSocket = 0;
    emit socketUnauthenticated( socket_uid, description );
}
