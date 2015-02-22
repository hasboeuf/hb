// Qt
// Hb
#include <HbGlobal.h>
#include <HbLogService.h>
// Local
#include <HbClientConnectionPool.h>
#include <com/tcp/HbTcpClient.h>
#include <service/presence/HbClientPresenceService.h>
#include <service/auth/HbClientAuthService.h>
#include <service/channel/HbClientChannelService.h>
#include <user/HbNetworkUser.h>

using namespace hb::network;


HbClientConnectionPool::HbClientConnectionPool()
{
    mMainClient = 0;
    /*HbClientPresenceService * service_timeout = new HbClientPresenceService();
    HbClientAuthService     * service_auth    = new HbClientAuthService();
    HbClientChannelService  * service_channel = new HbClientChannelService();

    mServices.insert( service_timeout->id(), service_timeout );
    mServices.insert( service_auth->id(),    service_auth    );
    mServices.insert( service_channel->id(), service_channel );

    foreach( HbNetworkService * service, mServices )
    {
        // Socket.
        IHbSocketListener * socket_listener = dynamic_cast< IHbSocketListener * >( service );
        if( socket_listener )
        {
            connect( this, &HbServerConnectionPool::socketConnected,
                    [socket_listener]( sockuid socket_uid )
                    {
                        socket_listener->onSocketConnected( socket_uid );
                    } );
            connect( this, &HbServerConnectionPool::socketDisconnected,
                    [socket_listener]( sockuid socket_uid )
                    {
                        socket_listener->onSocketDisconnected( socket_uid );
                    } );
        }
        // User.
        IHbUserListener * user_listener = dynamic_cast< IHbUserListener * >( service );
        if( user_listener )
        {
            connect( this, &HbServerConnectionPool::userConnected,
                    [user_listener]( const HbNetworkUserInfo & user_info )
                    {
                        user_listener->onUserConnected( user_info );
                    } );
            connect( this, &HbServerConnectionPool::userDisconnected,
                    [user_listener]( const HbNetworkUserInfo & user_info )
                    {
                        user_listener->onUserDisconnected( user_info );
                    } );
        }
    }*/
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

bool HbClientConnectionPool::setConfiguration( const HbGeneralClientConfig config )
{
    HbConnectionPool::setConfiguration( config );
}

sockuid HbClientConnectionPool::joinTcpClient( HbTcpClientConfig & config , bool main )
{
    sockuid uid = 0;
    if( main && mMainClient > 0 )
    {
        HbError( "Impossible to create two main clients." );
        return uid;
    }

    HbTcpClient * client = new HbTcpClient();

    setExchanges( config.exchanges() );

    client->setConfiguration( config );
    if( !client->join() )
    {
        delete client;
        return 0;
    }

    connect( client, &HbAbstractClient::clientConnected,    this, &HbClientConnectionPool::onClientConnected,    Qt::UniqueConnection );
    connect( client, &HbAbstractClient::clientDisconnected, this, &HbClientConnectionPool::onClientDisconnected, Qt::UniqueConnection );

    uid = client->uid();

    mClients.insert( uid, client );
    if( main )
    {
        mMainClient = uid;
    }

    return uid;
}

void HbClientConnectionPool::onClientConnected( sockuid client_uid )
{
    /*HbAbstractServer * server = dynamic_cast< HbAbstractServer * >( sender() );
    q_assert_ptr( server );
    q_assert( !mServers.contains( server_uid ) );

    HbInfo( "Server #%d connected.", server_uid );

    connect( server, &HbAbstractServer::serverConnected,        this, &HbServerConnectionPool::onServerConnected,        Qt::UniqueConnection );
    connect( server, &HbAbstractServer::serverDisconnected,     this, &HbServerConnectionPool::onServerDisconnected,     Qt::UniqueConnection );
    connect( server, &HbAbstractServer::socketConnected,        this, &HbServerConnectionPool::onSocketConnected,        Qt::UniqueConnection );
    connect( server, &HbAbstractServer::socketDisconnected,     this, &HbServerConnectionPool::onSocketDisconnected,     Qt::UniqueConnection );
    connect( server, &HbAbstractServer::socketContractReceived, this, &HbServerConnectionPool::onSocketContractReceived, Qt::UniqueConnection );

    mServers.insert( server->uid(), server );*/
}

void HbClientConnectionPool::onClientDisconnected( sockuid client_uid )
{
    /*HbAbstractServer * server = dynamic_cast< HbAbstractServer * >( sender() );
    q_assert_ptr( server );
    q_assert( mServers.contains( server_uid ) );

    HbInfo( "Server #%d disconnected.", server_uid );*/
}

void HbClientConnectionPool::onClientContractReceived( sockuid client_uid, const HbNetworkContract * contract )
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

void HbClientConnectionPool::onUserConnected( sockuid client_uid, const HbNetworkUserInfo & user_info )
{

}
