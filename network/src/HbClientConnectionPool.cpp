// Qt
// Hb
#include <HbGlobal.h>
#include <HbLogService.h>
#include <facebook/HbO2ClientFacebook.h>
// Local
#include <HbClientConnectionPool.h>
#include <com/tcp/HbTcpClient.h>
#include <service/presence/HbClientPresenceService.h>
#include <service/auth/HbClientAuthService.h>
#include <service/channel/HbClientChannelService.h>
#include <service/auth/HbClientAuthLoginObject.h>
#include <user/HbNetworkUser.h>

using namespace hb::network;


HbClientConnectionPool::HbClientConnectionPool( const HbGeneralClientConfig & config ) :
    HbConnectionPool( config )
{
    HbClientPresenceService * service_presence = new HbClientPresenceService();
    HbClientAuthService     * service_auth     = new HbClientAuthService();
    HbClientChannelService  * service_channel  = new HbClientChannelService();

    service_presence->setConfig( config.presence() );
    service_auth->setConfig    ( config.auth    () );
    service_channel->setConfig ( config.channel () );

    mServices.insert( service_presence->id(), service_presence );
    mServices.insert( service_auth->id(),     service_auth    );
    mServices.insert( service_channel->id(),  service_channel );

    foreach( HbNetworkService * service, mServices )
    {
        // Socket.
        IHbSocketListener * socket_listener = dynamic_cast< IHbSocketListener * >( service );
        if( socket_listener )
        {
            connect( this, &HbClientConnectionPool::socketConnected,
                    [socket_listener]( networkuid socket_uid )
                    {
                        socket_listener->onSocketConnected( socket_uid );
                    } );
            connect( this, &HbClientConnectionPool::socketDisconnected,
                    [socket_listener]( networkuid socket_uid )
                    {
                        socket_listener->onSocketDisconnected( socket_uid );
                    } );
        }
        // User.
        IHbUserListener * user_listener = dynamic_cast< IHbUserListener * >( service );
        if( user_listener )
        {
            connect( this, &HbClientConnectionPool::userConnected,
                    [user_listener]( const HbNetworkUserInfo & user_info )
                    {
                        user_listener->onUserConnected( user_info );
                    } );
            connect( this, &HbClientConnectionPool::userDisconnected,
                    [user_listener]( const HbNetworkUserInfo & user_info )
                    {
                        user_listener->onUserDisconnected( user_info );
                    } );
        }
    }

    connect( &mUser, &HbNetworkUser::statusChanged, this, &HbClientConnectionPool::onMeStatusChanged );
}

HbClientConnectionPool::~HbClientConnectionPool()
{
    leave();
}

bool HbClientConnectionPool::leave()
{
    qDeleteAll( mClients );
    mClients.clear();
    return true;
}

networkuid HbClientConnectionPool::joinTcpClient( HbTcpClientConfig & config , bool main )
{
    networkuid uid = 0;
    if( mUser.socketUid() > 0 )
    {
        HbError( "Impossible to create two main clients." );
        return uid;
    }

    HbTcpClient * client = new HbTcpClient();

    setExchanges( config.exchanges() );

    client->setConfiguration( config );

    connect( client, &HbAbstractClient::clientConnected,    this, &HbClientConnectionPool::onClientConnected,    Qt::UniqueConnection );
    connect( client, &HbAbstractClient::clientDisconnected, this, &HbClientConnectionPool::onClientDisconnected, Qt::UniqueConnection );

    if( !client->join() )
    {
        delete client;
        return 0;
    }

    uid = client->uid();

    mClients.insert( uid, client );
    if( main )
    {
        mUser.setSocketUid( uid );
    }

    return uid;
}

bool HbClientConnectionPool::authRequest( HbClientAuthLoginObject * login_object )
{
    if( !login_object )
    {
        HbError( "Login object null." );
        return false;
    }

    if( !mUser.status() != HbNetworkProtocol::USER_CONNECTED )
    {
        HbError( "User not in a connected state." );
        return false;
    }

    HbClientAuthService * auth_service = getService< HbClientAuthService >( HbNetworkProtocol::SERVICE_AUTH );
    q_assert_ptr( auth_service );

    login_object->setSocketUid( mUser.socketUid() );
    mUser.setStatus( HbNetworkProtocol::USER_AUTHENTICATING );

    auth_service->onAuthRequest( login_object );

    return false;
}

void HbClientConnectionPool::onClientConnected( networkuid client_uid )
{
    HbAbstractClient * client = dynamic_cast< HbAbstractClient * >( sender() );
    q_assert_ptr( client );
    q_assert( !mClients.contains( client_uid ) );

    connect( client, &HbAbstractClient::clientContractReceived, this, &HbClientConnectionPool::onClientContractReceived, Qt::UniqueConnection );

    mClients.insert( client->uid(), client );

    HbInfo( "Client %d connected.", client_uid );

    emit statusChanged( client_uid, HbNetworkProtocol::CLIENT_CONNECTED );
}

void HbClientConnectionPool::onClientDisconnected( networkuid client_uid )
{
    HbAbstractClient * client = dynamic_cast< HbAbstractClient * >( sender() );
    q_assert_ptr( client );
    q_assert( mClients.contains( client_uid ) );

    HbInfo( "Client #%d disconnected.", client_uid );

    emit statusChanged( client_uid, HbNetworkProtocol::CLIENT_DISCONNECTED );
}

void HbClientConnectionPool::onClientContractReceived( networkuid client_uid, const HbNetworkContract * contract )
{
    /*HbAbstractServer * server = dynamic_cast< HbAbstractServer * >( sender() );
    q_assert_ptr( server );
    q_assert( mServers.contains( server_uid ) );

    HbInfo( "Contract received from socket #%d on server #%d.", socket_uid, server_uid );


    if( !checkContractReceived( contract ) )
    {
        HbWarning( "Invalid contract received from socket #%d on server #%d. Kick scheduled.", socket_uid, server_uid );
        // TODO kick
        delete contract;
        return;
    }

    servuid requested_service = contract->header().service();

    HbInfo( "Contract OK [socket=%d, server=%d, service=%s, code=%s].",
            socket_uid,
            server_uid,
            HbLatin1( HbNetworkProtocol::MetaService::toString( requested_service ) ),
            HbLatin1( HbNetworkProtocol::MetaCode::toString( contract->header().code() ) ) );

    HbNetworkUser * user = isSocketAuthenticated( socket_uid );
    if( !user )
    {
        q_assert( requested_service == HbNetworkProtocol::SERVICE_AUTH );
    }

    HbNetworkService * service = mServices.value( requested_service, nullptr );
    if( !service )
    {
        // TODO kick
        HbError( "Service %s is not instanciated.", HbLatin1( HbNetworkProtocol::MetaService::toString( contract->header().service() ) ) );
        return;
    }

    service->onContractReceived( contract );*/
}

void HbClientConnectionPool::onContractSent( const HbNetworkContract * contract )
{

}

void HbClientConnectionPool::onUserConnected( networkuid client_uid, const HbNetworkUserInfo & user_info )
{

}

void HbClientConnectionPool::onMeStatusChanged( HbNetworkProtocol::UserStatus status )
{
    emit meStatusChanged( status );
}
