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
    mTimerId = startTimer( 1000 );
}

HbServerAuthService::~HbServerAuthService()
{
    qDeleteAll( mStrategies );
}

const HbServiceAuthServerConfig & HbServerAuthService::config() const
{
    return mConfig;
}

void HbServerAuthService::setConfig( const HbServiceAuthServerConfig & config )
{
    if( config.isValid() )
    {
        mConfig = config;
    }
}

void HbServerAuthService::addStrategy( HbServerAuthStrategy * strategy )
{
    if( strategy && !mStrategies.contains( strategy->type() ) )
    {
        mStrategies.insert( strategy->type(), strategy );

        connect( strategy, &HbServerAuthStrategy::authFailed,
                 this,     &HbServerAuthService::onAuthFailed, Qt::UniqueConnection );
        connect( strategy, &HbServerAuthStrategy::authSucceed,
                 this,     &HbServerAuthService::onAuthSucceed, Qt::UniqueConnection );
    }
    else
    {
        HbWarning( "Strategy already defined or null." );
    }
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

bool HbServerAuthService::checkSocket( networkuid socket_uid )
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

void HbServerAuthService::addSocket( networkuid socket_uid )
{
    mPendingSocket.insert( socket_uid );
    mAuthTimeout.insert  ( socket_uid, mConfig.authTimeout() );
    mAuthTries.insert    ( socket_uid, 0 );
}

void HbServerAuthService::delSocket( networkuid socket_uid, bool delete_responses )
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

void HbServerAuthService::kickSocket( networkuid socket_uid, HbNetworkProtocol::KickCode reason )
{
    delSocket( socket_uid );
    // TODO kick
}

void HbServerAuthService::onContractReceived( const HbNetworkContract * contract )
{

    const HbAuthRequestContract * auth_contract = contract->value< HbAuthRequestContract >();
    if( auth_contract )
    {
        authstgy   type       = auth_contract->type();
        networkuid socket_uid = auth_contract->sender();

        HbServerAuthStrategy * strategy = mStrategies.value( type, nullptr );
        if( strategy )
        {
            HbAuthStatusContract * response = auth_contract->reply();
            if( response &&
                response->receiver() == socket_uid )
            {

                mResponses.insert( socket_uid, response );

                if( strategy->checkLogin( auth_contract ) )
                {
                    q_assert( mAuthTries.contains( socket_uid ) );
                    mAuthTries[socket_uid]++;
                }
                else
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

void HbServerAuthService::onSocketConnected   ( networkuid socket_uid )
{
    addSocket( socket_uid );
}

void HbServerAuthService::onSocketDisconnected( networkuid socket_uid )
{
    delSocket( socket_uid );
}

void HbServerAuthService::onAuthSucceed( networkuid socket_uid, const HbNetworkUserInfo & user_info )
{
    if( checkSocket( socket_uid ) )
    {
        HbAuthStatusContract * response = mResponses.value( socket_uid, nullptr );
        if( !response )
        {
            kickSocket( socket_uid, HbNetworkProtocol::KICK_INTERNAL_ERROR );
            return;
        }

        emit socketAuthenticated( socket_uid, user_info );

        response->setStatus( HbNetworkProtocol::AUTH_OK );
        response->setTryNumber( 1 ); // TODO store try number.
        response->setMaxTries( mConfig.authMaxTries() );
        response->setUserInfo( user_info );

        delSocket( socket_uid, false );

        emit readyContractToSend( response );
    }
    else
    {
        HbWarning( "Socket %d disconnected before getting ok auth response.", socket_uid );
    }
}

void HbServerAuthService::onAuthFailed( networkuid socket_uid, HbNetworkProtocol::AuthStatus status, const QString & description )
{
    if( checkSocket( socket_uid ) )
    {
        HbAuthStatusContract * response = mResponses.value( socket_uid, nullptr );
        if( !response )
        {
            kickSocket( socket_uid, HbNetworkProtocol::KICK_INTERNAL_ERROR );
            return;
        }

        q_assert( mAuthTries.contains( socket_uid ) );

        response->setStatus( status );
        response->setDescription( description );
        response->setTryNumber( mAuthTries[socket_uid] );
        response->setMaxTries( mConfig.authMaxTries() );

        emit readyContractToSend( response );

        if( mAuthTries[socket_uid] == mConfig.authMaxTries() )
        {
            kickSocket( socket_uid, HbNetworkProtocol::KICK_AUTH_LIMIT );
        }
    }
    else
    {
        HbWarning( "Socket %d disconnected before getting nok auth response.", socket_uid );
    }
}
