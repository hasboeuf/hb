// Qt
// Hb
#include <HbGlobal.h>
#include <HbLogService.h>
// Local
#include <HbServerConnectionPool.h>
#include <com/tcp/HbTcpServer.h>
#include <contract/general/HbKickContract.h>
#include <service/presence/HbServerPresenceService.h>
#include <service/auth/HbServerAuthService.h>
#include <service/auth/HbServerAuthFacebookStrategy.h>
#include <service/channel/HbServerChannelService.h>
#include <user/HbNetworkUser.h>

using namespace hb::network;

HbServerConnectionPool::HbServerConnectionPool( const HbGeneralServerConfig & config ) :
    HbConnectionPool( config )
{
    mMainServer = 0;

    HbServerPresenceService * service_presence = new HbServerPresenceService();
    HbServerAuthService     * service_auth     = new HbServerAuthService();
    HbServerChannelService  * service_channel  = new HbServerChannelService();

    service_presence->setConfig( config.presence() );
    service_auth->setConfig    ( config.auth    () );
    service_channel->setConfig ( config.channel () );

    // Facebook auth
    if( config.auth().facebookAuthConfig().isValid() )
    {
        HbServerAuthFacebookStrategy * fb_strategy = new HbServerAuthFacebookStrategy();
        fb_strategy->setConfig( config.auth().facebookAuthConfig() );
        service_auth->addStrategy( fb_strategy );
    }

    mServices.insert( service_presence->id(), service_presence );
    mServices.insert( service_auth->id(),     service_auth    );
    mServices.insert( service_channel->id(),  service_channel );

    connect( service_auth,     &HbAuthService::socketAuthenticated,    this, &HbConnectionPool::onSocketAuthenticated,   Qt::UniqueConnection );
    connect( service_auth,     &HbAuthService::socketUnauthenticated,  this, &HbConnectionPool::onSocketUnauthenticated, Qt::UniqueConnection );
    connect( service_presence, &HbServerPresenceService::socketLagged, this, &HbServerConnectionPool::onSocketLagged,    Qt::UniqueConnection );

    foreach( HbNetworkService * service, mServices )
    {
        // Contract.
        //connect( service, &HbNetworkService::socketContractToSend, this, &HbConnectionPool::onSocketContractToSend );
        //connect( service, &HbNetworkService::userContractToSend,   this, &HbConnectionPool::onUserContractToSend   );
        connect( service, &HbNetworkService::readyContractToSend,  this, &HbConnectionPool::onReadyContractToSend  );

        // Kick
        connect( service, &HbNetworkService::userToKick,   this, &HbServerConnectionPool::onUserToKick );
        connect( service, &HbNetworkService::socketToKick, this, &HbServerConnectionPool::onSocketToKick );

        // Socket.
        IHbSocketListener * socket_listener = dynamic_cast< IHbSocketListener * >( service );
        if( socket_listener )
        {
            connect( this, &HbConnectionPool::socketConnected,
                    [socket_listener]( networkuid socket_uid )
                    {
                        socket_listener->onSocketConnected( socket_uid );
                    } );
            connect( this, &HbConnectionPool::socketDisconnected,
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
            connect( this, &HbConnectionPool::userConnected,
                    [user_listener]( const HbNetworkUserInfo & user_info )
                    {
                        user_listener->onUserConnected( user_info );
                    } );
            connect( this, &HbConnectionPool::userDisconnected,
                    [user_listener]( const HbNetworkUserInfo & user_info )
                    {
                        user_listener->onUserDisconnected( user_info );
                    } );
        }
    }
}

HbServerConnectionPool::~HbServerConnectionPool()
{
    leave();
}

bool HbServerConnectionPool::leave()
{
    qDeleteAll( mServers );
    mServers.clear();
    return true;
}

networkuid HbServerConnectionPool::joinTcpServer( HbTcpServerConfig & config , bool main )
{
    networkuid uid = 0;
    if( main && mMainServer > 0 )
    {
        HbError( "Impossible to create two main clients." );
        return uid;
    }

    HbTcpServer * server = new HbTcpServer();

    setExchanges( config.exchanges() );

    config.setBadHeaderTolerant( false ); // Force header checking.
    server->setConfiguration( config );

    connect( server, &HbAbstractServer::serverConnected,    this, &HbServerConnectionPool::onServerConnected,    Qt::UniqueConnection );
    connect( server, &HbAbstractServer::serverDisconnected, this, &HbServerConnectionPool::onServerDisconnected, Qt::UniqueConnection );

    if( !server->join() )
    {
        delete server;
        return 0;
    }

    uid = server->uid();

    mServers.insert( uid, server );
    if( main )
    {
        mMainServer = uid;
    }

    return uid;
}

void HbServerConnectionPool::onServerConnected( networkuid server_uid )
{
    HbAbstractServer * server = dynamic_cast< HbAbstractServer * >( sender() );
    q_assert_ptr( server );
    q_assert( !mServers.contains( server_uid ) );

    connect( server, &HbAbstractServer::socketConnected,        this, &HbServerConnectionPool::onSocketConnected,        Qt::UniqueConnection );
    connect( server, &HbAbstractServer::socketDisconnected,     this, &HbServerConnectionPool::onSocketDisconnected,     Qt::UniqueConnection );
    connect( server, &HbAbstractServer::socketContractReceived, this, &HbServerConnectionPool::onSocketContractReceived, Qt::UniqueConnection );

    mServers.insert( server->uid(), server );

    HbInfo( "Server %d connected.", server_uid );

    emit statusChanged( server_uid, HbNetworkProtocol::SERVER_LISTENING );
}

void HbServerConnectionPool::onServerDisconnected( networkuid server_uid )
{
    HbAbstractServer * server = dynamic_cast< HbAbstractServer * >( sender() );
    q_assert_ptr( server );
    q_assert( mServers.contains( server_uid ) );

    mServers.remove( server_uid );
    if( mMainServer == server_uid )
    {
        mMainServer = 0;
    }

    server->deleteLater();

    HbInfo( "Server %d disconnected.", server_uid );

    emit statusChanged( server_uid, HbNetworkProtocol::SERVER_DISCONNECTED );
}

void HbServerConnectionPool::onSocketConnected( networkuid server_uid, networkuid socket_uid )
{
    HbAbstractServer * server = dynamic_cast< HbAbstractServer * >( sender() );
    q_assert_ptr( server );
    q_assert( mServers.contains( server_uid ) );

    HbInfo( "Socket %d on server %d connected.", server_uid, socket_uid );

    mPendingSockets.insert( socket_uid );
    mServerBySocketId.insert( socket_uid, server_uid );

    auto listeners = getListeners< IHbSocketListener >();
    foreach( IHbSocketListener * listener, listeners )
    {
        listener->onSocketConnected( socket_uid );
    }

}

void HbServerConnectionPool::onSocketDisconnected( networkuid server_uid, networkuid socket_uid )
{
    HbAbstractServer * server = dynamic_cast< HbAbstractServer * >( sender() );
    q_assert_ptr( server );
    q_assert( mServers.contains( server_uid ) );
    q_assert( mServerBySocketId.contains( socket_uid ) );
    q_assert( mPendingSockets.contains( socket_uid ) || mUserBySocketId.contains( socket_uid ) );

    mServerBySocketId.remove( socket_uid );

    HbNetworkUser * user = isSocketAuthenticated( socket_uid );
    if( !user )
    {
        HbInfo( "Unauthenticated socket %d on server %d disconnected.", server_uid, socket_uid );

        mPendingSockets.remove( socket_uid );

        QList< IHbSocketListener * > listeners = getListeners< IHbSocketListener >();
        foreach( IHbSocketListener * listener, listeners )
        {
            listener->onSocketDisconnected( socket_uid );
        }
    }
    else
    {
        q_assert( mUserByEmail.contains( user->info().email() ) );
        mUserByEmail.remove( user->info().email() );
        mUserBySocketId.remove( socket_uid );

        const HbNetworkUserInfo user_info = user->info();
        delete user;

        QList< IHbUserListener * > listeners = getListeners< IHbUserListener >();
        foreach( IHbUserListener * listener, listeners )
        {
            listener->onUserDisconnected( user_info );
        }
    }
}

void HbServerConnectionPool::onSocketContractReceived( networkuid server_uid, networkuid socket_uid, const HbNetworkContract * contract )
{
    HbAbstractServer * server = dynamic_cast< HbAbstractServer * >( sender() );
    q_assert_ptr( server );
    q_assert( mServers.contains( server_uid ) );

    HbInfo( "Contract received from socket %d on server %d.", socket_uid, server_uid );

    serviceuid requested_service = contract->header().service();

    HbInfo( "Contract OK [socket=%d, server=%d, service=%s, code=%s].",
            socket_uid,
            server_uid,
            HbLatin1( HbNetworkProtocol::MetaService::toString( requested_service ) ),
            HbLatin1( HbNetworkProtocol::MetaCode::toString( contract->header().code() ) ) );

    HbNetworkUser * user = isSocketAuthenticated( socket_uid );
    if( !user )
    {
        q_assert( requested_service == HbNetworkProtocol::SERVICE_AUTH );
    }

    HbNetworkService * service = getService( requested_service );
    if( !service )
    {
        kickSocket( socket_uid, HbNetworkProtocol::KICK_CONTRACT_INVALID, "Bad service." );
        HbError( "Service %s is not instanciated.", HbLatin1( HbNetworkProtocol::MetaService::toString( contract->header().service() ) ) );
        return;
    }

    service->onContractReceived( contract );
}

void HbServerConnectionPool::onSocketContractToSend( networkuid receiver, HbNetworkContract * contract )
{
    q_assert_ptr( contract );

    networkuid server_uid = mServerBySocketId.value( receiver, 0 );

    HbAbstractServer * server = mServers.value( server_uid, nullptr );

    q_assert_ptr( server );

    contract->setRouting( HbNetworkProtocol::ROUTING_UNICAST );
    contract->addSocketReceiver( receiver );

    server->send( ShConstHbNetworkContract( contract ) );
}

void HbServerConnectionPool::onUserContractToSend  ( const HbNetworkUserInfo & user_info, HbNetworkContract * contract )
{
    HbNetworkUser * user = getUser( user_info );
    if( !user )
    {
        HbWarning( "User %d is disconnected. Contract not sent." );
        delete contract;
        return;
    }

    foreach( networkuid socket_uid, user->socketsUid() )
    {
        contract->addSocketReceiver( socket_uid );
    }
}

void HbServerConnectionPool::onReadyContractToSend ( const HbNetworkContract * contract )
{
    q_assert_ptr( contract );

    if( contract->isValid() )
    {
        auto receivers = contract->receivers();
        foreach( networkuid receiver, receivers )
        {
            networkuid server_uid = mServerBySocketId.value( receiver, 0 );
            if( server_uid > 0 )
            {
                HbAbstractServer * server = mServers.value( server_uid, nullptr ); // TODO will send many times the same contract if there are several servers.
                if( server )
                {
                    server->send( ShConstHbNetworkContract( contract ) );
                }
                else
                {
                    HbWarning( "Server %d does not exist.", server_uid );
                }
            }
            else
            {
                HbWarning( "Receiver %d has no associated server.", receiver );
            }
        }
    }
    else
    {
        HbWarning( "Try to send an invalid contract." );
    }
}

void HbServerConnectionPool::onUserToKick  ( const HbNetworkUserInfo & user_info, netwint reason, const QString & description )
{
    HbNetworkUser * user = getUser( user_info );
    q_assert_ptr( user );

    kickUser( user, reason, description );
}

void HbServerConnectionPool::onSocketToKick( networkuid socket_uid, netwint reason, const QString & description )
{
    q_assert( mServerBySocketId.contains( socket_uid ) );

    HbNetworkUser * user = mUserBySocketId.value( socket_uid, nullptr );
    if( user )
    {
        kickUser( user, reason, description );
    }
    else
    {
        kickSocket( socket_uid, reason, description );
    }
}

void HbServerConnectionPool::kickUser( HbNetworkUser * user, netwint reason, const QString & description )
{
    q_assert_ptr( user );

    foreach( networkuid socket_uid, user->socketsUid() )
    {
        kickSocket( socket_uid, reason, description );
    }
}

void HbServerConnectionPool::kickSocket( networkuid socket_uid , netwint reason, const QString & description )
{
    networkuid server_uid = mServerBySocketId.value( socket_uid, 0 );
    q_assert( server_uid > 0 );

    HbAbstractServer * server = mServers.value( server_uid );

    q_assert( server );

    HbKickContract * kick_contract = new HbKickContract();
    kick_contract->addSocketReceiver( socket_uid );
    kick_contract->setReason     ( reason );
    kick_contract->setDescription( description );

    server->send( ShConstHbNetworkContract( kick_contract ) );
    server->leave( socket_uid );
}

void HbServerConnectionPool::onSocketAuthenticated  ( networkuid socket_uid, const HbNetworkUserInfo & user_info )
{    
    if( !mServerBySocketId.contains( socket_uid ) )
    {
        HbWarning( "Socket %d disconnected before being authenticated.", socket_uid );
        return;
    }

    HbNetworkUser * user = new HbNetworkUser();
    user->setInfo( user_info );
    user->setMainSocketUid( socket_uid );

    mPendingSockets.remove( socket_uid );
    mUserBySocketId.insert( socket_uid, user );
    mUserByEmail.insert( user_info.email(), user );

    emit socketAuthenticated( socket_uid );
}

void HbServerConnectionPool::onSocketUnauthenticated( networkuid socket_uid, quint8 try_number, quint8 max_tries, const QString & reason )
{
    Q_UNUSED( try_number )
    Q_UNUSED( max_tries )
    Q_UNUSED( reason )

    q_assert( mUserBySocketId.contains( socket_uid ) );

    HbNetworkUser * user = mUserBySocketId.value( socket_uid, nullptr );
    q_assert_ptr( user );
    q_assert( user->mainSocketUid() == socket_uid );
    q_assert( mUserByEmail.contains( user->info().email() ) );

    user->setMainSocketUid( 0 );
    mUserByEmail.remove( user->info().email() );

    foreach( networkuid socket, user->socketsUid() )
    {
        mUserBySocketId.remove( socket );
    }

    delete user;

    // TODO send reason to HbServer.

    emit socketUnauthenticated( socket_uid );
}

void HbServerConnectionPool::onSocketLagged( networkuid socket_uid, quint16 last_presence, quint16 kick_threshold )
{
    HbWarning( "Socket %d lagged since %d seconds, %d seconds before kick.",
               socket_uid,
               last_presence,
               kick_threshold - last_presence );
}

HbNetworkUser * HbServerConnectionPool::isSocketAuthenticated( networkuid socket_uid )
{
    return mUserBySocketId.value( socket_uid, nullptr );
}

HbNetworkUser * HbServerConnectionPool::getUser( const HbNetworkUserInfo & user_info )
{
    return mUserByEmail.value( user_info.email(), nullptr );
}
