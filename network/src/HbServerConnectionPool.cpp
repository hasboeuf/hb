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
#include <user/HbServerUser.h>

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

    mServices.insert( service_presence->uid(), service_presence );
    mServices.insert( service_auth->uid(),     service_auth    );
    mServices.insert( service_channel->uid(),  service_channel );

    connect( service_auth,     &HbAuthService::socketAuthenticated,    this, &HbConnectionPool::onSocketAuthenticated,   Qt::UniqueConnection );
    connect( service_auth,     &HbAuthService::socketUnauthenticated,  this, &HbConnectionPool::onSocketUnauthenticated, Qt::UniqueConnection );
    connect( service_presence, &HbServerPresenceService::socketLagged, this, &HbServerConnectionPool::onSocketLagged,    Qt::UniqueConnection );

    foreach( HbNetworkService * service, mServices )
    {
        q_assert_ptr( service );

        // From services.
        connect( service, &HbNetworkService::contractToSend,      this, &HbServerConnectionPool::onContractToSend );
        connect( service, &HbNetworkService::userContractToSend,  this, &HbServerConnectionPool::onUserContractToSend );
        connect( service, &HbNetworkService::usersContractToSend, this, &HbServerConnectionPool::onUsersContractToSend );
        connect( service, &HbNetworkService::userToKick,          this, &HbServerConnectionPool::onUserToKick );
        connect( service, &HbNetworkService::socketToKick,        this, &HbServerConnectionPool::onSocketToKick );

        // To services.
        // Contract listener.
        IHbContractListener * contract_listener = dynamic_cast< IHbContractListener * >( service );
        if( contract_listener )
        {
            connect( this, &HbConnectionPool::socketContractReceived,
                    [contract_listener]( const HbNetworkContract * contract )
                    {
                        contract_listener->onContractReceived( contract );
                    } );
        }

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
                    [user_listener]( ShConstHbNetworkUserInfo user_info )
                    {
                        user_listener->onUserConnected( user_info );
                    } );
            connect( this, &HbConnectionPool::userDisconnected,
                    [user_listener]( ShConstHbNetworkUserInfo user_info )
                    {
                        user_listener->onUserDisconnected( user_info );
                    } );
        }

        // User contract listener.
        IHbServerUserContractListener * user_contract_listener = dynamic_cast< IHbServerUserContractListener * >( service );
        if( user_contract_listener )
        {
            connect( this, &HbConnectionPool::userContractReceived,
                    [user_contract_listener]( ShConstHbNetworkUserInfo user_info, const HbNetworkContract * contract )
                    {
                        user_contract_listener->onUserContractReceived( user_info, contract );
                    } );
        }
    }
}

HbServerConnectionPool::~HbServerConnectionPool()
{
    leave();
}

networkuid HbServerConnectionPool::joinTcpServer( HbTcpServerConfig & config , bool main )
{
    networkuid network_uid = 0;
    if( main && mMainServer > 0 )
    {
        HbError( "Impossible to create two main clients." );
        return network_uid;
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

    network_uid = server->uid();

    foreach( HbNetworkChannel * channel, config.channels() )
    {
        if( addChannel( channel ) )
        {
            channel->setNetworkUid( network_uid );
        }
    }

    mServers.insert( network_uid, server );
    if( main )
    {
        mMainServer = network_uid;
    }

    return network_uid;
}

bool HbServerConnectionPool::leave()
{
    mLeaving = true;

    QHash< networkuid, HbAbstractServer * > copy = mServers;
    // Local copy as onClientDisconnected remove items of mServers bit by bit.
    qDeleteAll( copy );

    // onServerDisconnected is called there and handles:
    // - mMainServer
    // - mServers
    // onSocketDisconnected will not be fired.

    mPendingSockets.clear();
    qDeleteAll( mUserBySocketId );
    mUserBySocketId.clear();
    mUserByEmail.clear();
    mServerBySocketId.clear();

    // Reset
    HbConnectionPool::reset(); // Reset services.

    mLeaving = false;

    q_assert( mMainServer == 0 );
    q_assert( mServers.isEmpty() );
    q_assert( mPendingSockets.isEmpty() );
    q_assert( mServerBySocketId.isEmpty() );
    q_assert( mUserBySocketId.isEmpty() );
    q_assert( mUserByEmail.isEmpty() );

    return true;
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

    emit statusChanged( server_uid, HbNetworkProtocol::SERVER_DISCONNECTED );

    mServers.remove( server_uid );

    if( mLeaving )
    {
        HbInfo( "HbServer is leaving. Server %d removed.", server_uid );
        // Deletion is handled in leave().
    }
    else
    {
        HbInfo( "Server %d disconnected.", server_uid );
        server->deleteLater( );
    }

    if( mMainServer == server_uid )
    {
        HbInfo( "Server %d was the main server, reset.", server_uid );
        mMainServer = 0;
    }
}

void HbServerConnectionPool::onSocketConnected( networkuid server_uid, networkuid socket_uid )
{
    q_assert( mServers.contains( server_uid ) );

    HbInfo( "Socket %d on server %d connected.", server_uid, socket_uid );

    mPendingSockets.insert( socket_uid );
    mServerBySocketId.insert( socket_uid, server_uid );

    emit socketConnected( socket_uid ); // To IHbSocketListener.
}

void HbServerConnectionPool::onSocketDisconnected( networkuid server_uid, networkuid socket_uid )
{
    q_assert( mServers.contains( server_uid ) );
    q_assert( mServerBySocketId.contains( socket_uid ) );
    q_assert( mPendingSockets.contains( socket_uid ) || mUserBySocketId.contains( socket_uid ) );

    mServerBySocketId.remove( socket_uid );

    HbServerUser * user = isSocketAuthenticated( socket_uid );
    if( !user )
    {
        HbInfo( "Unauthenticated socket %d on server %d disconnected.", server_uid, socket_uid );

        mPendingSockets.remove( socket_uid );

        emit socketDisconnected( socket_uid ); // To IHbSocketListener.
    }
    else
    {
        q_assert( mUserByEmail.contains( user->info().data()->email() ) );
        mUserByEmail.remove( user->info()->email() );
        mUserBySocketId.remove( socket_uid );

        delete user;

        // Notifying...
        emit socketUnauthenticated( socket_uid ); // To IHbSocketAuthListener.
        emit userDisconnected( user->info() ); // To IHbUserListener.
    }
}

void HbServerConnectionPool::onSocketContractReceived( networkuid server_uid, networkuid socket_uid, const HbNetworkContract * contract )
{
    q_assert( mServers.contains( server_uid ) );

    HbInfo( "Contract received from socket %d on server %d.", socket_uid, server_uid );

    serviceuid requested_service = contract->header().service();

    HbInfo( "Contract OK [socket=%d, server=%d, service=%s, code=%s].",
            socket_uid,
            server_uid,
            HbLatin1( HbNetworkProtocol::MetaService::toString( requested_service ) ),
            HbLatin1( HbNetworkProtocol::MetaCode::toString( contract->header().code() ) ) );

    HbServerUser * user = isSocketAuthenticated( socket_uid );
    if( !user )
    {
        if( requested_service != HbNetworkProtocol::SERVICE_AUTH )
        {
            kickSocket( socket_uid, HbNetworkProtocol::KICK_CONTRACT_INVALID, "Bad service." );
            HbError( "Unauthenticated socket requested a service.", HbLatin1( HbNetworkProtocol::MetaService::toString( contract->header().service() ) ) );
            return;
        }
    }

    HbNetworkService * service = getService( requested_service );
    if( !service )
    {
        kickSocket( socket_uid, HbNetworkProtocol::KICK_CONTRACT_INVALID, "Bad service." );
        HbError( "Service %s is not instanciated.", HbLatin1( HbNetworkProtocol::MetaService::toString( contract->header().service() ) ) );
        return;
    }

    // A service can process exclusively unauth contract or auth contract.

    IHbContractListener * unauth_service = dynamic_cast< IHbContractListener * >(service);
    if( unauth_service )
    {
        unauth_service->onContractReceived( contract );
    }
    else
    {
        q_assert_ptr( user );
        IHbServerUserContractListener * auth_service = dynamic_cast< IHbServerUserContractListener * >(service);
        q_assert_ptr( auth_service );
        auth_service->onUserContractReceived( user->info(), contract );
    }
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

void HbServerConnectionPool::onUsersContractToSend( QList< ShConstHbNetworkUserInfo > users_infos, HbNetworkContract * contract )
{
    q_assert_ptr( contract );
    networkuid server_uid = contract->networkReceiver();
    q_assert( server_uid != 0 );
    q_assert( contract->receivers().size() == 0 );

    foreach( ShConstHbNetworkUserInfo user_info, users_infos )
    {
        HbServerUser * user = getUser( user_info );
        if( !user )
        {
            HbWarning( "User %d is disconnected." );
            break;
        }

        networkuid socket_uid = user->socketUid( server_uid );
        contract->addSocketReceiver( socket_uid );
    }

    onContractToSend( contract );
}

void HbServerConnectionPool::onUserContractToSend( ShConstHbNetworkUserInfo user_info, HbNetworkContract * contract )
{
    q_assert_ptr( contract );
    networkuid server_uid = contract->networkReceiver();
    q_assert( server_uid != 0 );
    q_assert( contract->receivers().size() == 0 );

    HbServerUser * user = getUser( user_info );
    if( !user )
    {
        HbWarning( "User %d is disconnected. Contract not sent." );
        delete contract;
        return;
    }

    networkuid socket_uid = user->socketUid( server_uid );
    contract->addSocketReceiver( socket_uid );

    onContractToSend( contract );
}

void HbServerConnectionPool::onContractToSend ( const HbNetworkContract * contract )
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
                HbAbstractServer * server = mServers.value( server_uid, nullptr ); //! \todo Will send many times the same contract if there are several servers.
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

void HbServerConnectionPool::onUserToKick( ShConstHbNetworkUserInfo user_info, netwint reason, const QString & description )
{
    HbServerUser * user = getUser( user_info );
    q_assert_ptr( user );

    kickUser( user, reason, description );
}

void HbServerConnectionPool::onSocketToKick( networkuid socket_uid, netwint reason, const QString & description )
{
    q_assert( mServerBySocketId.contains( socket_uid ) );

    HbServerUser * user = mUserBySocketId.value( socket_uid, nullptr );
    if( user )
    {
        kickUser( user, reason, description );
    }
    else
    {
        kickSocket( socket_uid, reason, description );
    }
}

void HbServerConnectionPool::kickUser( HbServerUser * user, netwint reason, const QString & description )
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

void HbServerConnectionPool::onSocketAuthenticated( networkuid socket_uid, const HbNetworkUserInfo & user_info )
{
    if( !mServerBySocketId.contains( socket_uid ) )
    {
        HbWarning( "Socket %d disconnected before being authenticated.", socket_uid );
        return;
    }

    HbServerUser * user = new HbServerUser();
    user->setInfo( user_info );

    q_assert( mServerBySocketId.contains( socket_uid ) );

    networkuid server_uid = mServerBySocketId.value( socket_uid );

    user->addSocket( server_uid, socket_uid, true );

    mPendingSockets.remove( socket_uid );
    mUserBySocketId.insert( socket_uid, user );
    mUserByEmail.insert( user_info.email(), user );

    emit socketAuthenticated( socket_uid ); // To IHbSocketAuthListener.
    emit userConnected( user->info() );     // To IHbUserListener.
}

void HbServerConnectionPool::onSocketUnauthenticated( networkuid socket_uid, quint8 try_number, quint8 max_tries, const QString & reason )
{
    Q_UNUSED( try_number )
    Q_UNUSED( max_tries )
    Q_UNUSED( reason )

    q_assert( mUserBySocketId.contains( socket_uid ) );

    HbServerUser * user = mUserBySocketId.value( socket_uid, nullptr );
    q_assert_ptr( user );
    q_assert( user->mainSocketUid() == socket_uid );
    q_assert( mUserByEmail.contains( user->info().data()->email() ) );

    mUserByEmail.remove( user->info().data()->email() );

    foreach( networkuid socket, user->socketsUid() )
    {
        mUserBySocketId.remove( socket );
    }

    //! \todo Send reason to HbServer.

    emit socketUnauthenticated( socket_uid );

    delete user;
}

void HbServerConnectionPool::onSocketLagged( networkuid socket_uid, quint16 last_presence, quint16 kick_threshold )
{
    HbWarning( "Socket %d lagged since %d seconds, %d seconds before kick.",
               socket_uid,
               last_presence,
               kick_threshold - last_presence );
}

HbServerUser * HbServerConnectionPool::isSocketAuthenticated( networkuid socket_uid )
{
    return mUserBySocketId.value( socket_uid, nullptr );
}

HbServerUser * HbServerConnectionPool::getUser( ShConstHbNetworkUserInfo user_info )
{
    return mUserByEmail.value( user_info->email(), nullptr );
}
