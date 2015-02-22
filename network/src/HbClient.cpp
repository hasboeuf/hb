// Qt
// Hb
#include <HbLogService.h>
// Local
#include <HbClient.h>
#include <com/tcp/HbTcpClient.h>

using namespace hb::network;

HbClient::HbClient( const HbGeneralClientConfig & config ) :
    HbPeer( config )
{
    mConnectionPool.setConfiguration( config );
}

bool HbClient::leave()
{
    mConnectionPool.leave();
    return true;
}

sockuid HbClient::joinTcpClient( HbTcpClientConfig & config , bool main )
{
    return mConnectionPool.joinTcpClient( config, main );
}

/*void HbClient::onClientConnected( sockuid client_uid )
{
    HbInfo( "Client %d connected.", client_uid );
    emit clientConnected( client_uid );
}

void HbClient::onClientDisconnected    ( sockuid client_uid )
{
    HbInfo( "Client %d disconnected.", client_uid );

    q_assert( mClients.contains( client_uid ) );

    HbAbstractClient * client = mClients.take( client_uid );
    if( mMainClient == client )
    {
        mMainClient = nullptr;
    }
    client->deleteLater();

    emit clientDisconnected( client_uid );
}*/


