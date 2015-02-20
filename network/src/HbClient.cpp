// Qt
// Hb
// Local
#include <HbClient.h>
#include <com/tcp/HbTcpClient.h>

using namespace hb::network;

HbClient::HbClient( const HbGeneralClientConfig & config ) :
    HbPeer( config )
{

}

bool HbClient::leave()
{

}

quint16 HbClient::joinTcpClient( const HbTcpClientConfig & config )
{
    HbTcpClient * client = new HbTcpClient();

    connect( client, &HbAbstractClient::clientConnected,    this, &HbClient::onClientConnected,    Qt::UniqueConnection );
    connect( client, &HbAbstractClient::clientDisconnected, this, &HbClient::onClientDisconnected, Qt::UniqueConnection );

    q_assert( !mClients.contains( client->uid() ) );

    client->setConfiguration( config );

    if( !client->join() )
    {
        delete client;
        return 0;
    }
    return client->uid();
}

void HbClient::onClientConnected       ( sockuid client_uid )
{

}

void HbClient::onClientDisconnected    ( sockuid client_uid )
{

}

void HbClient::onClientContractReceived( sockuid client_uid, const HbNetworkContract * contract )
{

}

void HbClient::onContractSent( const HbNetworkContract * contract )
{

}

void HbClient::onUserConnected   ( sockuid client_uid )
{

}

void HbClient::onUserDisconnected( sockuid client_uid )
{

}


