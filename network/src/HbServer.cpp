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

bool HbServer::joinTcpServer( const HbTcpServerConfig & config )
{
    HbTcpServer * server = new HbTcpServer();
    server->setConfiguration( config );

    bool ok = server->join();
    if( !ok )
    {
        delete server;
    }
    else
    {
        mServers.insert( server->uuid(), server );
    }

    return ok;
}

bool HbServer::leave()
{
    qDeleteAll( mServers );
    mServers.clear();
}
