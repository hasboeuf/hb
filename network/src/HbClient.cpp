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
        connect( &mConnectionPool, &HbClientConnectionPool::statusChanged,   this, &HbClient::clientStatusChanged ); // Signal to signal.
        connect( &mConnectionPool, &HbClientConnectionPool::meStatusChanged, this, &HbClient::meStatusChanged );     // Signal to signal.
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

bool HbClient::OAuthRequested( HbAuthService::AuthType type )
{
    if( !isReady() ) return false;
    if( type == HbAuthService::AUTH_NONE &&
        type >= HbAuthService::AUTH_USER )
    {
        return false;
    }

    HbClientAuthLoginObject * login_object = new HbClientAuthLoginObject();
    login_object->setStrategy( type );
    return mConnectionPool.authRequested( login_object );
}

