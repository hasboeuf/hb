// Qt
// Hb
#include <HbGlobal.h>
#include <HbLogService.h>
// Local
#include <HbServerConnectionPool.h>
#include <com/tcp/HbTcpServer.h>
#include <service/presence/HbServerPresenceService.h>
#include <service/auth/HbServerAuthService.h>
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

    mServices.insert( service_presence->id(), service_presence );
    mServices.insert( service_auth->id(),     service_auth    );
    mServices.insert( service_channel->id(),  service_channel );

    //connect( service_auth, &HbServerAuthService::userConnected, this, &HbConnectionPool::onUserConnected );

    foreach( HbNetworkService * service, mServices )
    {
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

    server->setConfiguration( config );
    if( !server->join() )
    {
        delete server;
        return 0;
    }

    connect( server, &HbAbstractServer::serverConnected,    this, &HbServerConnectionPool::onServerConnected,    Qt::UniqueConnection );
    connect( server, &HbAbstractServer::serverDisconnected, this, &HbServerConnectionPool::onServerDisconnected, Qt::UniqueConnection );

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

    HbInfo( "Server #%d connected.", server_uid );

    connect( server, &HbAbstractServer::serverConnected,        this, &HbServerConnectionPool::onServerConnected,        Qt::UniqueConnection );
    connect( server, &HbAbstractServer::serverDisconnected,     this, &HbServerConnectionPool::onServerDisconnected,     Qt::UniqueConnection );
    connect( server, &HbAbstractServer::socketConnected,        this, &HbServerConnectionPool::onSocketConnected,        Qt::UniqueConnection );
    connect( server, &HbAbstractServer::socketDisconnected,     this, &HbServerConnectionPool::onSocketDisconnected,     Qt::UniqueConnection );
    connect( server, &HbAbstractServer::socketContractReceived, this, &HbServerConnectionPool::onSocketContractReceived, Qt::UniqueConnection );

    mServers.insert( server->uid(), server );
}

void HbServerConnectionPool::onServerDisconnected( networkuid server_uid )
{
    HbAbstractServer * server = dynamic_cast< HbAbstractServer * >( sender() );
    q_assert_ptr( server );
    q_assert( mServers.contains( server_uid ) );

    HbInfo( "Server #%d disconnected.", server_uid );
}

void HbServerConnectionPool::onSocketConnected( networkuid server_uid, networkuid socket_uid )
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

void HbServerConnectionPool::onSocketDisconnected( networkuid server_uid, networkuid socket_uid )
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

void HbServerConnectionPool::onSocketContractReceived( networkuid server_uid, networkuid socket_uid, const HbNetworkContract * contract )
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
        // TODO kick
        HbError( "Service %s is not instanciated.", HbLatin1( HbNetworkProtocol::MetaService::toString( contract->header().service() ) ) );
        return;
    }

    service->onContractReceived( contract );
}

void HbServerConnectionPool::onContractSent( const HbNetworkContract * contract )
{

}

void HbServerConnectionPool::onContractSent( networkuid socket_uid, const HbNetworkContract * contract )
{

}

void HbServerConnectionPool::onUserKick( const HbNetworkUser & user_info, netwint reason )
{

}

void HbServerConnectionPool::onSocketKick( networkuid socket_uid, netwint reason )
{

}

void HbServerConnectionPool::onUserConnected( networkuid socket_id, const HbNetworkUserInfo & user_info )
{

}

HbNetworkUser * HbServerConnectionPool::isSocketAuthenticated( networkuid socket_uid )
{
    return mUserBySocketId.value( socket_uid, nullptr );
}
