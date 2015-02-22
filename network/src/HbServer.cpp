// Qt
// Hb
// Local
#include <HbServer.h>
#include <com/tcp/HbTcpServer.h>
#include <config/com/HbTcpServerConfig.h>

using namespace hb::network;

HbServer::HbServer(const HbGeneralServerConfig & config ) :
    HbPeer( config ), mConnectionPool( config )
{
    if( isReady() )
    {
        connect( &mConnectionPool, &HbConnectionPool::statusChanged, this, &HbPeer::statusChanged );
    }
}

networkuid HbServer::joinTcpServer( HbTcpServerConfig & config , bool main )
{
    return mConnectionPool.joinTcpServer( config, main );
}

bool HbServer::leave()
{
    return mConnectionPool.leave();
}
