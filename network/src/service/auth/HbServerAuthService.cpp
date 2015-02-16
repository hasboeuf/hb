// Qt
// Hb
#include <HbLogService.h>
// Local
#include <service/auth/HbServerAuthService.h>
#include <service/auth/HbServerAuthStrategy.h>
#include <contract/auth/HbAuthRequestContract.h>
#include <contract/auth/HbAuthFacebookRequestContract.h>
#include <contract/auth/HbAuthStatusContract.h>
#include <service/auth/HbServerAuthFacebookStrategy.h>

using namespace hb::network;

HbServerAuthService::HbServerAuthService()
{
    mUuid = HbNetworkProtocol::SERVICE_AUTH;

    HbServerAuthFacebookStrategy * fb_strategy = new HbServerAuthFacebookStrategy();
    mStrategies.insert( fb_strategy->type(), fb_strategy );

    foreach( HbServerAuthStrategy * strategy, mStrategies )
    {
        if( strategy )
        {
            connect( strategy, &HbServerAuthStrategy::loginFailed,
                     this,     &HbServerAuthService::onLoginFailed, Qt::UniqueConnection );
            connect( strategy, &HbServerAuthStrategy::loginSucceed,
                     this,     &HbServerAuthService::onLoginSucceed, Qt::UniqueConnection );
        }
    }

    mTimerId = startTimer( 1000 );
}

HbServerAuthService::~HbServerAuthService()
{
    qDeleteAll( mStrategies );
}

HbNetworkProtocol::NetworkTypes HbServerAuthService::enabledNetworkTypes() const
{
    return HbNetworkProtocol::NETWORK_TCP |
           HbNetworkProtocol::NETWORK_SSL;
}

void HbServerAuthService::timerEvent( QTimerEvent * )
{
    // TODO check socket timeout.
}

void HbServerAuthService::onContractReceived( const HbNetworkContract * contract )
{
    const HbAuthRequestContract * auth_contract = contract->value< const HbAuthRequestContract >();
    if( auth_contract )
    {
        authstgy type = auth_contract->type();

        HbServerAuthStrategy * strategy = mStrategies.value( type, nullptr );
        if( strategy )
        {

            if( strategy->tryLogin( auth_contract ) )
            {
                // TODO retrieve reply now ?
            }
            else
            {
                HbError( "Bad contract." );
                // TODO kick?
            }
        }
        else
        {
            HbError( "No user auth strategy defined." );
            // TODO kick?
        }
    }
    else
    {
        HbError( "Auth contract type not recognized." );
        // TODO kick?
    }
}

void HbServerAuthService::onSocketConnected   ( sockuuid socket_uuid )
{
    mPendingSocket.insert( socket_uuid );
}

void HbServerAuthService::onSocketDisconnected( sockuuid socket_uuid )
{
    mPendingSocket.remove( socket_uuid );
}

void HbServerAuthService::onLoginSucceed( sockuuid sender, const HbNetworkUserInfo & user_info )
{
    if( mPendingSocket.contains( sender ) )
    {
        emit userConnected( sender, user_info );

        HbAuthStatusContract * response = new HbAuthStatusContract();
        response->setStatus( HbNetworkProtocol::AUTH_OK );
        response->setTryNumber( 1 ); // TODO store try number.
        response->setMaxTries( 3 ); // TODO config.

        mPendingSocket.remove( sender );
    }
    else
    {
        HbWarning( "Socket %d disconnected before getting ok auth response.", sender );
    }
}

void HbServerAuthService::onLoginFailed( sockuuid sender, HbNetworkProtocol::AuthStatus, const QString & description )
{
    if( mPendingSocket.contains( sender ) )
    {
        mPendingSocket.remove( sender );

        // TODO retrieve or create the reply.
        // TODO think about number of tries.
    }
    else
    {
        HbWarning( "Socket %d disconnected before getting nok auth response.", sender );
    }
}
