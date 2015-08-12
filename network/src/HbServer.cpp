// Qt
// Hb
#include <service/channel/HbServerChannel.h>
// Local
#include <HbServer.h>
#include <com/tcp/HbTcpServer.h>
#include <config/com/HbTcpServerConfig.h>
#include <service/channel/HbNetworkChannel.h>

using namespace hb::network;

HbServer::HbServer(const HbGeneralServerConfig & config ) :
    HbPeer( config ), mConnectionPool( config )
{
    if( isReady() )
    {
        connect( &mConnectionPool, &HbServerConnectionPool::statusChanged, this, &HbServer::serverStatusChanged );
    }
}

networkuid HbServer::joinTcpServer( HbTcpServerConfig & config , bool main )
{
    if( !isReady() ) return false;
    return mConnectionPool.joinTcpServer( config, main );
}

bool HbServer::leave()
{
    if( !isReady() ) return false;
    return mConnectionPool.leave();
}

bool HbServer::registerChannel( HbNetworkChannel * channel )
{
    return mConnectionPool.addChannel( channel );
}
