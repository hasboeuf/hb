// Qt
// Hb
#include <HbGlobal.h>
#include <HbLogService.h>
// Local
#include <HbConnectionPool.h>
#include <com/tcp/HbTcpServer.h>
#include <service/timeout/HbNetworkTimeoutService.h>
#include <service/auth/HbNetworkAuthenticationService.h>
#include <service/channel/HbNetworkChannelService.h>

using namespace hb::network;


HbConnectionPool::HbConnectionPool()
{
    HbNetworkTimeoutService        * service_timeout        = new HbNetworkTimeoutService();
    HbNetworkAuthenticationService * service_authentication = new HbNetworkAuthenticationService();
    HbNetworkChannelService        * service_channel        = new HbNetworkChannelService();

    q_assert( service_timeout->id()        != HbNetworkProtocol::SERVICE_UNDEFINED );
    q_assert( service_authentication->id() != HbNetworkProtocol::SERVICE_UNDEFINED );
    q_assert( service_channel->id()        != HbNetworkProtocol::SERVICE_UNDEFINED );

    mServices.insert( service_timeout->uuid(),        service_timeout );
    mServices.insert( service_authentication->uuid(), service_authentication );
    mServices.insert( service_channel->uuid(),        service_channel );


}

HbConnectionPool::~HbConnectionPool()
{
    leave();
}

bool HbConnectionPool::leave()
{
    qDeleteAll( mServers );
    mServers.clear();
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
}

void HbConnectionPool::onSocketDisconnected( quint16 server_uuid, sockuuid socket_uuid )
{
    HbAbstractServer * server = dynamic_cast< HbAbstractServer * >( sender() );
    q_assert_ptr( server );
    q_assert( !mServers.contains( server_uuid ) );

    HbInfo( "Socket #%d on server #%d disconnected.", server_uuid, socket_uuid );
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
        // Kick socket.
        delete contract;
        return;
    }

    HbInfo( "Contract OK [socket=%d, server=%d].", socket_uuid, server_uuid );

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
