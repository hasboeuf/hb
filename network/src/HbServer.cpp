// Qt
// Hb
// Local
#include <HbServer.h>
#include <com/tcp/HbTcpServer.h>
#include <config/com/HbTcpServerConfig.h>

using namespace hb::network;

HbServer::HbServer(const HbGeneralServerConfig &config ) :
    HbPeer( config )
{
    mConnectionPool.setConfiguration( config );
}

netwuid HbServer::joinTcpServer( HbTcpServerConfig & config , bool main )
{
    return mConnectionPool.joinTcpServer( config, main );
}

bool HbServer::leave()
{
    mConnectionPool.leave();
    return true;
}
