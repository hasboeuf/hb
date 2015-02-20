// Qt
// Hb
#include <HbGlobal.h>
#include <HbLogService.h>
// Local
#include <HbConnectionPool.h>
#include <com/tcp/HbTcpServer.h>
#include <service/presence/HbServerPresenceService.h>
#include <service/auth/HbServerAuthService.h>
#include <service/channel/HbServerChannelService.h>
#include <user/HbNetworkUser.h>

using namespace hb::network;


HbConnectionPool::HbConnectionPool()
{
    HbServerPresenceService * service_timeout = new HbServerPresenceService();
    HbServerAuthService     * service_auth    = new HbServerAuthService();
    HbServerChannelService  * service_channel = new HbServerChannelService();

    q_assert( service_timeout->id() != HbNetworkProtocol::SERVICE_UNDEFINED );
    q_assert( service_auth->id()    != HbNetworkProtocol::SERVICE_UNDEFINED );
    q_assert( service_channel->id() != HbNetworkProtocol::SERVICE_UNDEFINED );

    mServices.insert( service_timeout->id(), service_timeout );
    mServices.insert( service_auth->id(),    service_auth    );
    mServices.insert( service_channel->id(), service_channel );

    //connect( service_auth, &HbServerAuthService::userConnected, this, &HbConnectionPool::onUserConnected );

    foreach( HbNetworkService * service, mServices )
    {
        // Socket.
        IHbSocketListener * socket_listener = dynamic_cast< IHbSocketListener * >( service );
        if( socket_listener )
        {
            connect( this, &HbConnectionPool::socketConnected,
                    [socket_listener]( sockuid socket_uid )
                    {
                        socket_listener->onSocketConnected( socket_uid );
                    } );
            connect( this, &HbConnectionPool::socketDisconnected,
                    [socket_listener]( sockuid socket_uid )
                    {
                        socket_listener->onSocketDisconnected( socket_uid );
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

HbConnectionPool::~HbConnectionPool()
{
    leave();
}

bool HbConnectionPool::leave()
{
    qDeleteAll( mServers );
    mServers.clear();
    return true;
}

quint16 HbConnectionPool::joinTcpServer( const HbTcpServerConfig & config )
{
    HbTcpServer * server = new HbTcpServer();

    connect( server, &HbAbstractServer::serverConnected,    this, &HbConnectionPool::onServerConnected,    Qt::UniqueConnection );
    connect( server, &HbAbstractServer::serverDisconnected, this, &HbConnectionPool::onServerDisconnected, Qt::UniqueConnection );

    q_assert( !mServers.contains( server->uid() ) );

    server->setConfiguration( config );

    if( !server->join() )
    {
        delete server;
        return 0;
    }
    return server->uid();
}

void HbConnectionPool::onServerConnected( quint16 server_uid )
{
    HbAbstractServer * server = dynamic_cast< HbAbstractServer * >( sender() );
    q_assert_ptr( server );
    q_assert( !mServers.contains( server_uid ) );

    HbInfo( "Server #%d connected.", server_uid );

    connect( server, &HbAbstractServer::serverConnected,        this, &HbConnectionPool::onServerConnected,        Qt::UniqueConnection );
    connect( server, &HbAbstractServer::serverDisconnected,     this, &HbConnectionPool::onServerDisconnected,     Qt::UniqueConnection );
    connect( server, &HbAbstractServer::socketConnected,        this, &HbConnectionPool::onSocketConnected,        Qt::UniqueConnection );
    connect( server, &HbAbstractServer::socketDisconnected,     this, &HbConnectionPool::onSocketDisconnected,     Qt::UniqueConnection );
    connect( server, &HbAbstractServer::socketContractReceived, this, &HbConnectionPool::onSocketContractReceived, Qt::UniqueConnection );

    mServers.insert( server->uid(), server );
}

void HbConnectionPool::onServerDisconnected( quint16 server_uid )
{
    HbAbstractServer * server = dynamic_cast< HbAbstractServer * >( sender() );
    q_assert_ptr( server );
    q_assert( mServers.contains( server_uid ) );

    HbInfo( "Server #%d disconnected.", server_uid );
}

void HbConnectionPool::onSocketConnected( quint16 server_uid, sockuid socket_uid )
{
    HbAbstractServer * server = dynamic_cast< HbAbstractServer * >( sender() );
    q_assert_ptr( server );
    q_assert( mServers.contains( server_uid ) );

    HbInfo( "Socket #%d on server #%d connected.", server_uid, socket_uid );

    mPendingSockets.insert( socket_uid );

    QList< IHbSocketListener * > listeners = getListeners< IHbSocketListener >();
    foreach( IHbSocketListener * listener, listeners )
    {
        listener->onSocketConnected( socket_uid );
    }

}

void HbConnectionPool::onSocketDisconnected( quint16 server_uid, sockuid socket_uid )
{
    HbAbstractServer * server = dynamic_cast< HbAbstractServer * >( sender() );
    q_assert_ptr( server );
    q_assert( !mServers.contains( server_uid ) );
    q_assert( mServerBySocketId.contains( socket_uid ) );
    q_assert( mPendingSockets.contains( socket_uid ) || mUserBySocketId.contains( socket_uid ) );

    mServerBySocketId.remove( socket_uid );

    HbNetworkUser * user = isSocketAuthenticated( socket_uid );
    if( !user )
    {
        HbInfo( "Unauthenticated socket #%d on server #%d disconnected.", server_uid, socket_uid );

        mPendingSockets.remove( socket_uid );

        QList< IHbSocketListener * > listeners = getListeners< IHbSocketListener >();
        foreach( IHbSocketListener * listener, listeners )
        {
            listener->onSocketDisconnected( socket_uid );
        }
    }
    else
    {
        mUserBySocketId.remove( socket_uid );

        const HbNetworkUserInfo user_info = user->userInfo();
        delete user;

        QList< IHbUserListener * > listeners = getListeners< IHbUserListener >();
        foreach( IHbUserListener * listener, listeners )
        {
            listener->onUserDisconnected( user_info );
        }
    }
}

void HbConnectionPool::onSocketContractReceived( quint16 server_uid, sockuid socket_uid, const HbNetworkContract * contract )
{
    HbAbstractServer * server = dynamic_cast< HbAbstractServer * >( sender() );
    q_assert_ptr( server );
    q_assert( mServers.contains( server_uid ) );

    HbInfo( "Contract received from socket #%d on server #%d.", socket_uid, server_uid );


    if( !checkContractReceived( contract ) )
    {
        HbWarning( "Invalid contract received from socket #%d on server #%d. Kick scheduled.", socket_uid, server_uid );
        // TODO kick
        delete contract;
        return;
    }

    servuid requested_service = contract->header().service();

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

    HbNetworkService * service = mServices.value( requested_service, nullptr );
    if( !service )
    {
        // TODO kick
        HbError( "Service %s is not instanciated.", HbLatin1( HbNetworkProtocol::MetaService::toString( contract->header().service() ) ) );
        return;
    }

    service->onContractReceived( contract );
}

bool HbConnectionPool::checkContractReceived( const HbNetworkContract * contract )
{
    q_assert_ptr( contract );

    bool ok = true;

    if( ( contract->header().appName()         != HbNetworkProtocol::msAppName ) ||
        ( contract->header().protocolVersion() != HbNetworkProtocol::msProtocolVersion ) )
    {
        ok = false;
    }

    return ok;
}

HbNetworkUser * HbConnectionPool::isSocketAuthenticated( sockuid socket_uid )
{
    return mUserBySocketId.value( socket_uid, nullptr );
}
