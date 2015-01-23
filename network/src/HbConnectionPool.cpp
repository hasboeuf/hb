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

void HbConnectionPool::onSocketConnected( quint16 server_uuid, quint32 socket_uuid )
{
    HbAbstractServer * server = dynamic_cast< HbAbstractServer * >( sender() );
    q_assert_ptr( server );
    q_assert( mServers.contains( server_uuid ) );

    HbInfo( "Socket #%d on server #%d connected.", server_uuid, socket_uuid );
}

void HbConnectionPool::onSocketDisconnected( quint16 server_uuid, quint32 socket_uuid )
{
    HbAbstractServer * server = dynamic_cast< HbAbstractServer * >( sender() );
    q_assert_ptr( server );
    q_assert( !mServers.contains( server_uuid ) );


    HbInfo( "Socket #%d on server #%d disconnected.", server_uuid, socket_uuid );
}

void HbConnectionPool::onSocketContractReceived( quint16 server_uuid, const HbNetworkContract & contract )
{
    HbAbstractServer * server = dynamic_cast< HbAbstractServer * >( sender() );
    q_assert_ptr( server );
    q_assert( !mServers.contains( server_uuid ) );

    HbInfo( "Contract received for socket #%d on server #%d.", server_uuid, 0 ); // TODO contract sender ?
}
