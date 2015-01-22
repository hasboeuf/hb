// Qt
// Hb
// Local
#include <HbServer.h>
#include <com/tcp/HbTcpServer.h>
#include <config/HbTcpServerConfig.h>

using namespace hb::network;

HbServer::HbServer( const HbGeneralConfig & config ) :
    HbPeer( config )
{

}

quint16 HbServer::joinTcpServer( const HbTcpServerConfig & config )
{
    return mConnectionPool.joinTcpServer( config );
}

bool HbServer::leave()
{
    mConnectionPool.leave();
}
