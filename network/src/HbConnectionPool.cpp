// Qt
// Hb
#include <HbGlobal.h>
// Local
#include <HbConnectionPool.h>
#include <com/tcp/HbTcpServer.h>

using namespace hb::network;

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
    bool ok = server->join();
    if( !ok )
    {
        delete server;
        return 0;
    }
    else
    {
        mServers.insert( server->uuid(), server );
        return server->uuid();
    }
}
