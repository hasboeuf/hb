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

void HbServerAuthService::timerEvent( QTimerEvent * )
{
    // TODO check socket timeout.
    auto it = mAuthTimeout.begin();
    while( it != mAuthTimeout.end() )
    {
        auto current = it++;

    }
}

bool HbServerAuthService::checkSocket( sockuid socket_uid )
{
    quint8 flags = 0x0;
    if( mPendingSocket.contains( socket_uid ) ) flags |= 0x1;
    if( mAuthTimeout.contains  ( socket_uid ) ) flags |= 0x2;
    if( mAuthTries.contains    ( socket_uid ) ) flags |= 0x4;

    if( flags == 0x7 ) // All contains socket_uid.
    {
        return true;
    }
    else if( flags != 0x0 ) // Something incoherent is here, socket_uid is not present everywhere.
    {
        kickSocket( socket_uid, HbNetworkProtocol::KICK_INTERNAL_ERROR );
    }

    return false;
}

void HbServerAuthService::addSocket( sockuid socket_uid )
{
    mPendingSocket.insert( socket_uid );
    mAuthTimeout.insert  ( socket_uid, 30 ); // TODO config
    mAuthTries.insert    ( socket_uid, 0 );
}

void HbServerAuthService::delSocket( sockuid socket_uid, bool delete_responses )
{
    mPendingSocket.remove( socket_uid );
    mAuthTries.remove    ( socket_uid );
    mAuthTimeout.remove  ( socket_uid );

    // If auth is in process.
    if( delete_responses &&
        mResponses.value( socket_uid, nullptr ) )
    {
        delete mResponses.take( socket_uid );
    }
}

void HbServerAuthService::kickSocket( sockuid socket_uid, HbNetworkProtocol::KickCode reason )
{
    delSocket( socket_uid );
    // TODO kick
}

void HbServerAuthService::onContractReceived( const HbNetworkContract * contract )
{
    const HbAuthRequestContract * auth_contract = contract->value< const HbAuthRequestContract >();
    if( auth_contract )
    {
        authstgy type      = auth_contract->type();
        sockuid socket_uid = auth_contract->sender();

        HbServerAuthStrategy * strategy = mStrategies.value( type, nullptr );
        if( strategy )
        {
            HbAuthStatusContract * response = auth_contract->reply();
            if( response &&
                response->socketReceiver() == socket_uid )
            {

                mResponses.insert( socket_uid, response );

                if( !strategy->tryLogin( auth_contract ) )
                {
                    HbError( "Bad contract." );
                    delete mResponses.take( socket_uid );
                    // TODO kick?
                }
            }
            else
            {
                HbError( "Bad reply contract." );
                // TODO kick?
            }
        }
        else
        {
            HbError( "No user auth strategy defined." );
            // TODO kick?
        }

        delete auth_contract;
    }
    else
    {
        HbError( "Auth contract type not recognized." );
        // TODO kick?
    }
}

void HbServerAuthService::onSocketConnected   ( sockuid socket_uid )
{
    addSocket( socket_uid );
}

void HbServerAuthService::onSocketDisconnected( sockuid socket_uid )
{
    delSocket( socket_uid );
}

void HbServerAuthService::onLoginSucceed( sockuid socket_uid, const HbNetworkUserInfo & user_info )
{
    if( checkSocket( socket_uid ) )
    {
        HbAuthStatusContract * response = mResponses.value( socket_uid, nullptr );
        if( !response )
        {
            kickSocket( socket_uid, HbNetworkProtocol::KICK_INTERNAL_ERROR );
            return;
        }

        emit userConnected( socket_uid, user_info );

        response->setStatus( HbNetworkProtocol::AUTH_OK );
        response->setTryNumber( 1 ); // TODO store try number.
        response->setMaxTries( 3 ); // TODO config.

        delSocket( socket_uid, false );

        // TODO emit contract.
    }
    else
    {
        HbWarning( "Socket %d disconnected before getting ok auth response.", socket_uid );
    }
}

void HbServerAuthService::onLoginFailed( sockuid socket_uid, HbNetworkProtocol::AuthStatus status, const QString & description )
{
    if( checkSocket( socket_uid ) )
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
        response->setMaxTries( 3 ); // TODO config.

        // TODO emit contract.
    }
    else
    {
        HbWarning( "Socket %d disconnected before getting nok auth response.", socket_uid );
    }
}
