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

    q_assert( service_timeout->uuid() != HbNetworkProtocol::SERVICE_UNDEFINED );
    q_assert( service_auth->uuid()    != HbNetworkProtocol::SERVICE_UNDEFINED );
    q_assert( service_channel->uuid() != HbNetworkProtocol::SERVICE_UNDEFINED );

    mServices.insert( service_timeout->uuid(), service_timeout );
    mServices.insert( service_auth->uuid(),    service_auth    );
    mServices.insert( service_channel->uuid(), service_channel );

    foreach( HbNetworkService * service, mServices )
    {
        // Socket.
        IHbSocketListener * socket_listener = dynamic_cast< IHbSocketListener * >( service );
        if( socket_listener )
        {
            connect( this, &HbConnectionPool::socketConnected,
                    [socket_listener]( sockuuid socket_uuid )
                    {
                        socket_listener->onSocketConnected( socket_uuid );
                    } );
            connect( this, &HbConnectionPool::socketDisconnected,
                    [socket_listener]( sockuuid socket_uuid )
                    {
                        socket_listener->onSocketDisconnected( socket_uuid );
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

    connect( server, &HbAbstractServer::serverConnected,    this, &HbConnectionPool::onServerConnected );
    connect( server, &HbAbstractServer::serverDisconnected, this, &HbConnectionPool::onServerDisconnected );

    q_assert( !mServers.contains( server->uuid() ) );

    server->setConfiguration( config );

    if( !server->join() )
    {
        delete server;
        return 0;
    }
    return server->uuid();
}

void HbConnectionPool::onServerConnected( quint16 server_uuid )
{
    HbAbstractServer * server = dynamic_cast< HbAbstractServer * >( sender() );
    q_assert_ptr( server );
    q_assert( !mServers.contains( server_uuid ) );

    HbInfo( "Server #%d connected.", server_uuid );

    connect( server, &HbAbstractServer::serverConnected,        this, &HbConnectionPool::onServerConnected );
    connect( server, &HbAbstractServer::serverDisconnected,     this, &HbConnectionPool::onServerDisconnected );
    connect( server, &HbAbstractServer::socketConnected,        this, &HbConnectionPool::onSocketConnected );
    connect( server, &HbAbstractServer::socketDisconnected,     this, &HbConnectionPool::onSocketDisconnected );
    connect( server, &HbAbstractServer::socketContractReceived, this, &HbConnectionPool::onSocketContractReceived );

    mServers.insert( server->uuid(), server );
}

void HbConnectionPool::onServerDisconnected( quint16 server_uuid )
{
    HbAbstractServer * server = dynamic_cast< HbAbstractServer * >( sender() );
    q_assert_ptr( server );
    q_assert( mServers.contains( server_uuid ) );

    HbInfo( "Server #%d disconnected.", server_uuid );
}

void HbConnectionPool::onSocketConnected( quint16 server_uuid, sockuuid socket_uuid )
{
    HbAbstractServer * server = dynamic_cast< HbAbstractServer * >( sender() );
    q_assert_ptr( server );
    q_assert( mServers.contains( server_uuid ) );

    HbInfo( "Socket #%d on server #%d connected.", server_uuid, socket_uuid );

    mPendingSockets.insert( socket_uuid );

    QList< IHbSocketListener * > listeners = getListeners< IHbSocketListener >();
    foreach( IHbSocketListener * listener, listeners )
    {
        listener->onSocketConnected( socket_uuid );
    }

}

void HbConnectionPool::onSocketDisconnected( quint16 server_uuid, sockuuid socket_uuid )
{
    HbAbstractServer * server = dynamic_cast< HbAbstractServer * >( sender() );
    q_assert_ptr( server );
    q_assert( !mServers.contains( server_uuid ) );
    q_assert( mServerBySocketId.contains( socket_uuid ) );
    q_assert( mPendingSockets.contains( socket_uuid ) || mUserBySocketId.contains( socket_uuid ) );

    mServerBySocketId.remove( socket_uuid );

    HbNetworkUser * user = isSocketAuthenticated( socket_uuid );
    if( !user )
    {
        HbInfo( "Unauthenticated socket #%d on server #%d disconnected.", server_uuid, socket_uuid );

        mPendingSockets.remove( socket_uuid );

        QList< IHbSocketListener * > listeners = getListeners< IHbSocketListener >();
        foreach( IHbSocketListener * listener, listeners )
        {
            listener->onSocketDisconnected( socket_uuid );
        }
    }
    else
    {
        mUserBySocketId.remove( socket_uuid );

        const HbNetworkUserInfo user_info = user->userInfo();
        delete user;

        QList< IHbUserListener * > listeners = getListeners< IHbUserListener >();
        foreach( IHbUserListener * listener, listeners )
        {
            listener->onUserDisconnected( user_info );
        }
    }
}

void HbConnectionPool::onSocketContractReceived( quint16 server_uuid, sockuuid socket_uuid, const HbNetworkContract * contract )
{
    HbAbstractServer * server = dynamic_cast< HbAbstractServer * >( sender() );
    q_assert_ptr( server );
    q_assert( mServers.contains( server_uuid ) );

    HbInfo( "Contract received from socket #%d on server #%d.", socket_uuid, server_uuid );


    if( !checkContractReceived( contract ) )
    {
        HbWarning( "Invalid contract received from socket #%d on server #%d. Kick scheduled.", socket_uuid, server_uuid );
        // TODO kick
        delete contract;
        return;
    }

    servuuid requested_service = contract->header().service();

    HbInfo( "Contract OK [socket=%d, server=%d, service=%s, code=%s].",
            socket_uuid,
            server_uuid,
            HbLatin1( HbNetworkProtocol::MetaService::toString( requested_service ) ),
            HbLatin1( HbNetworkProtocol::MetaCode::toString( contract->header().code() ) ) );

    HbNetworkUser * user = isSocketAuthenticated( socket_uuid );
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

HbNetworkUser * HbConnectionPool::isSocketAuthenticated( sockuuid socket_uuid )
{
    return mUserBySocketId.value( socket_uuid, nullptr );
}
