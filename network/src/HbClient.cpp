// Qt
// Hb
#include <HbLogService.h>
#include <facebook/HbO2ClientFacebook.h>
// Local
#include <HbClient.h>
#include <service/auth/HbClientAuthLoginObject.h>
#include <com/tcp/HbTcpClient.h>
#include <service/channel/HbNetworkChannel.h>

using namespace hb::network;
using namespace hb::link;

HbClient::HbClient( const HbGeneralClientConfig & config ) :
    HbPeer( config ), mConnectionPool( config )
{
    if( isReady() )
    {
        connect( &mConnectionPool, &HbClientConnectionPool::statusChanged,   this, &HbClient::clientStatusChanged );
        connect( &mConnectionPool, &HbClientConnectionPool::meStatusChanged, this, &HbClient::meStatusChanged );
    }
}

networkuid HbClient::joinTcpClient( HbTcpClientConfig & config , bool main )
{
    if( !isReady() ) return false;
    return mConnectionPool.joinTcpClient( config, main );
}

bool HbClient::leave()
{
    if( !isReady() ) return false;
    return mConnectionPool.leave();
}

bool HbClient::authRequest( HbClientAuthLoginObject * login_object )
{
    if( !isReady() ) return false;
    return mConnectionPool.authRequested( login_object );
}

bool HbClient::facebookAuthRequested()
{
    if( !isReady() ) return false;

    HbClientAuthLoginObject * login_object = new HbClientAuthLoginObject();
    login_object->setStrategy( HbAuthService::AUTH_FACEBOOK );
    return mConnectionPool.authRequested( login_object );
}

/*void HbClient::onClientConnected( netwuid client_uid )
{
    HbInfo( "Client %d connected.", client_uid );
    emit clientConnected( client_uid );
}

void HbClient::onClientDisconnected    ( netwuid client_uid )
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


