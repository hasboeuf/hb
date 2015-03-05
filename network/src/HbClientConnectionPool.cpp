// Qt
// Hb
#include <HbGlobal.h>
#include <HbLogService.h>
#include <facebook/HbO2ClientFacebook.h>
// Local
#include <HbClientConnectionPool.h>
#include <com/tcp/HbTcpClient.h>
#include <service/presence/HbClientPresenceService.h>
#include <service/auth/HbClientAuthService.h>
#include <service/auth/HbClientAuthFacebookStrategy.h>
#include <service/channel/HbClientChannelService.h>
#include <service/auth/HbClientAuthLoginObject.h>
#include <user/HbNetworkUser.h>
#include <contract/general/HbKickContract.h>

using namespace hb::network;


HbClientConnectionPool::HbClientConnectionPool( const HbGeneralClientConfig & config ) :
    HbConnectionPool( config )
{
    HbClientPresenceService * service_presence = new HbClientPresenceService();
    HbClientAuthService     * service_auth     = new HbClientAuthService();
    HbClientChannelService  * service_channel  = new HbClientChannelService();

    service_presence->setConfig( config.presence() );
    service_auth->setConfig    ( config.auth    () );
    service_channel->setConfig ( config.channel () );

    // Facebook auth
    if( config.auth().facebookAuthConfig().isValid() )
    {
        HbClientAuthFacebookStrategy * fb_strategy = new HbClientAuthFacebookStrategy();
        fb_strategy->setConfig( config.auth().facebookAuthConfig() );
        service_auth->addStrategy( fb_strategy );
    }

    mServices.insert( service_presence->id(), service_presence );
    mServices.insert( service_auth->id(),     service_auth    );
    mServices.insert( service_channel->id(),  service_channel );

    connect( service_auth, &HbAuthService::socketAuthenticated,   this, &HbConnectionPool::onSocketAuthenticated,   Qt::UniqueConnection );
    connect( service_auth, &HbAuthService::socketUnauthenticated, this, &HbConnectionPool::onSocketUnauthenticated, Qt::UniqueConnection );

    foreach( HbNetworkService * service, mServices )
    {
        // Contract.
        //connect( service, &HbNetworkService::socketContractToSend, this, &HbConnectionPool::onSocketContractToSend );
        //connect( service, &HbNetworkService::userContractToSend,   this, &HbConnectionPool::onUserContractToSend   );
        connect( service, &HbNetworkService::readyContractToSend,  this, &HbConnectionPool::onReadyContractToSend  );

        // Socket.
        IHbSocketListener * socket_listener = dynamic_cast< IHbSocketListener * >( service );
        if( socket_listener )
        {
            connect( this, &HbClientConnectionPool::socketConnected,
                    [socket_listener]( networkuid socket_uid )
                    {
                        socket_listener->onSocketConnected( socket_uid );
                    } );
            connect( this, &HbClientConnectionPool::socketDisconnected,
                    [socket_listener]( networkuid socket_uid )
                    {
                        socket_listener->onSocketDisconnected( socket_uid );
                    } );
        }

        // Socket auth.
        IHbSocketAuthListener * socket_auth_listener = dynamic_cast< IHbSocketAuthListener * >( service );
        if( socket_auth_listener )
        {
            connect( this, &HbConnectionPool::socketAuthenticated,
                    [socket_auth_listener]( networkuid socket_uid )
                    {
                        socket_auth_listener->onSocketAuthenticated( socket_uid );
                    } );
            connect( this, &HbConnectionPool::socketUnauthenticated,
                    [socket_auth_listener]( networkuid socket_uid )
                    {
                        socket_auth_listener->onSocketUnauthenticated( socket_uid );
                    } );
        }

        // User.
        IHbUserListener * user_listener = dynamic_cast< IHbUserListener * >( service );
        if( user_listener )
        {
            connect( this, &HbClientConnectionPool::userConnected,
                    [user_listener]( const HbNetworkUserInfo & user_info )
                    {
                        user_listener->onUserConnected( user_info );
                    } );
            connect( this, &HbClientConnectionPool::userDisconnected,
                    [user_listener]( const HbNetworkUserInfo & user_info )
                    {
                        user_listener->onUserDisconnected( user_info );
                    } );
        }
    }

    connect( &mUser, &HbNetworkUser::statusChanged, this, &HbClientConnectionPool::onMeStatusChanged );
}

HbClientConnectionPool::~HbClientConnectionPool()
{
    leave();
}

bool HbClientConnectionPool::leave()
{
    mLeaving = true;

    QHash< networkuid, HbAbstractClient * > copy = mClients;
    // Local copy as onClientDisconnected remove items of mClients bit by bit.
    qDeleteAll( copy );
    // onClientDisconnected is called there.

    mUser.reset();

    mLeaving = false;
    return true;
}

networkuid HbClientConnectionPool::joinTcpClient( HbTcpClientConfig & config , bool main )
{
    networkuid uid = 0;
    if( mUser.mainSocketUid() > 0 )
    {
        HbError( "Impossible to create two main clients." );
        return uid;
    }

    HbTcpClient * client = new HbTcpClient();

    setExchanges( config.exchanges() );

    config.setBadHeaderTolerant( false ); // Force header checking.
    client->setConfiguration( config );

    connect( client, &HbAbstractClient::clientConnected,    this, &HbClientConnectionPool::onClientConnected,    Qt::UniqueConnection );
    connect( client, &HbAbstractClient::clientDisconnected, this, &HbClientConnectionPool::onClientDisconnected, Qt::UniqueConnection );

    if( !client->join() )
    {
        delete client;
        return 0;
    }

    uid = client->uid();

    mClients.insert( uid, client );
    if( main )
    {
        mUser.setMainSocketUid( uid );
    }

    return uid;
}

bool HbClientConnectionPool::authRequested( HbClientAuthLoginObject * login_object )
{
    if( !login_object )
    {
        HbError( "Login object null." );
        return false;
    }

    if( mUser.status() != HbNetworkProtocol::USER_CONNECTED )
    {
        HbError( "User not in a connected state." );
        return false;
    }

    HbClientAuthService * auth_service = getService< HbClientAuthService >( HbNetworkProtocol::SERVICE_AUTH );
    q_assert_ptr( auth_service );

    login_object->setSocketUid( mUser.mainSocketUid() );
    mUser.setStatus( HbNetworkProtocol::USER_AUTHENTICATING );

    auth_service->onAuthRequested( login_object );

    return false;
}

void HbClientConnectionPool::onClientConnected( networkuid client_uid )
{
    HbAbstractClient * client = dynamic_cast< HbAbstractClient * >( sender() );
    q_assert_ptr( client );
    q_assert( mClients.contains( client_uid ) );

    connect( client, &HbAbstractClient::clientContractReceived, this, &HbClientConnectionPool::onClientContractReceived, Qt::UniqueConnection );

    HbInfo( "Client %d connected.", client_uid );

    emit statusChanged( client_uid, HbNetworkProtocol::CLIENT_CONNECTED );

    if( client_uid == mUser.mainSocketUid() )
    {
        mUser.setStatus( HbNetworkProtocol::USER_CONNECTED );
    }
}

void HbClientConnectionPool::onClientDisconnected( networkuid client_uid )
{
    HbAbstractClient * client = dynamic_cast< HbAbstractClient * >( sender() );
    q_assert_ptr( client );
    q_assert( mClients.contains( client_uid ) );

    emit statusChanged( client_uid, HbNetworkProtocol::CLIENT_DISCONNECTED );

    bool reconnecting = ( client->configuration().reconnectionDelay() > 0 ? true : false );
    if( mLeaving ) // If HbClient is leaving.
    {
        HbInfo( "HbClient is leaving. Client %d removed.", client_uid );
        mClients.remove( client_uid );
        // Deletion is handled in leave().
        // User reset is done in leave().
    }
    else
    {
        HbInfo( "Client %d disconnected.", client_uid );
        if( !reconnecting )
        {
            HbInfo( "Client %d will not reconnect, deletion...", client_uid );
            mClients.remove( client_uid );
            client->deleteLater();

            if( client_uid == mUser.mainSocketUid( ) )
            {
                HbInfo( "Client %d was the main client, reset.", client_uid );
                mUser.reset();
            }
        }
        else
        {
            if( client_uid == mUser.mainSocketUid() )
            {
                mUser.reset();
                mUser.setMainSocketUid( client_uid ); // Keep the main socket as it will reconnect.
            }
        }
    }
}

void HbClientConnectionPool::onClientContractReceived( networkuid client_uid, const HbNetworkContract * contract )
{
    HbAbstractClient * client = dynamic_cast< HbAbstractClient * >( sender() );
    q_assert_ptr( client );
    q_assert( mClients.contains( client_uid ) );

    HbInfo( "Contract received from client %d.", client_uid );

    serviceuid requested_service = contract->header().service();

    HbInfo( "Contract OK [client=%d, service=%s, code=%s].",
            client_uid,
            HbLatin1( HbNetworkProtocol::MetaService::toString( requested_service ) ),
            HbLatin1( HbNetworkProtocol::MetaCode::toString( contract->header().code() ) ) );

    if( checkKickReceived( contract ) )
    {
        delete contract;
        return;
    }

    if( mUser.status() != HbNetworkProtocol::USER_AUTHENTICATED )
    {
        q_assert( requested_service == HbNetworkProtocol::SERVICE_AUTH );
    }

    HbNetworkService * service = getService( requested_service );
    if( !service )
    {
        HbError( "Service %s is not instanciated.", HbLatin1( HbNetworkProtocol::MetaService::toString( contract->header().service() ) ) );
        return;
    }

    service->onContractReceived( contract );
}

/*void HbClientConnectionPool::onSocketContractToSend( networkuid receiver, HbNetworkContract * contract )
{
    q_assert_ptr( contract );

    HbAbstractClient * client = mClients.value( receiver, nullptr );
    if( !client )
    {
        HbWarning( "Client disconnected, can not send contract." );
        delete contract;
        return;
    }

    client->send( ShHbNetworkContract( contract ) );
}

void HbClientConnectionPool::onUserContractToSend  ( const HbNetworkUserInfo & user, HbNetworkContract * contract )
{

}*/

void HbClientConnectionPool::onReadyContractToSend ( const HbNetworkContract * contract )
{
    if( contract->isValid() )
    {
        auto receivers = contract->receivers();
        foreach( networkuid receiver, receivers )
        {
            HbAbstractClient * client = mClients.value( receiver, nullptr );
            if( client )
            {
                client->send( ShConstHbNetworkContract( contract ) );
            }
            else
            {
                HbWarning( "Receiver %d does not exist.", receiver );
            }
        }
    }
    else
    {
        HbWarning( "Try to send an invalid contract." );
    }
}

void HbClientConnectionPool::onSocketAuthenticated( networkuid socket_uid, const HbNetworkUserInfo & user_info )
{
    q_assert( socket_uid > 0 );

    if( mUser.mainSocketUid() == socket_uid )
    {
        mUser.setInfo( user_info );
        mUser.setStatus( HbNetworkProtocol::USER_AUTHENTICATED );
        HbInfo( "User %s (me) is authenticated.", HbLatin1( user_info.email() ) );
    }

    HbInfo( "Socket %d authenticated.", socket_uid );

    emit socketAuthenticated( socket_uid );
}

void HbClientConnectionPool::onSocketUnauthenticated( networkuid socket_uid, quint8 try_number, quint8 max_tries, const QString & reason )
{
    q_assert( socket_uid > 0 );

    if( mUser.mainSocketUid() == socket_uid )
    {
        mUser.setInfo( HbNetworkUserInfo() );
        mUser.setStatus( HbNetworkProtocol::USER_CONNECTED );
        HbInfo( "User (me) is unauthenticated." );
    }

    HbInfo( "Socket %d unauthenticated (try_number=%d, max_tries=%d, reason=%s).",
            socket_uid,
            try_number,
            max_tries,
            HbLatin1( reason ) );

    // TODO send reason to HbClient.

    emit socketUnauthenticated( socket_uid );
}

void HbClientConnectionPool::onMeStatusChanged( HbNetworkProtocol::UserStatus status )
{
    emit meStatusChanged( status );
}

bool HbClientConnectionPool::checkKickReceived( const HbNetworkContract * contract )
{
    q_assert_ptr( contract );

    if( contract->header().service() == HbNetworkProtocol::SERVICE_KICK &&
        contract->header().code()    == HbNetworkProtocol::CODE_SRV_KICK )
    {
        const HbKickContract * kick_contract = contract->value< HbKickContract >();
        q_assert_ptr( kick_contract );

        HbError( "Kick contract received! (reason=%s, description=%s)",
                 HbLatin1( HbNetworkProtocol::MetaKickCode::toString( kick_contract->reason() ) ),
                 HbLatin1( kick_contract->description() ) );

        // TODO tell it to HbClient.

        return true;
    }

    return false;
}
