// Qt
// Hb
// Local
#include <service/auth/HbServerAuthService.h>
#include <service/auth/HbServerAuthStrategy.h>
#include <contract/auth/HbAuthRequestContract.h>

using namespace hb::network;

HbServerAuthService::HbServerAuthService()
{
    mUuid = HbNetworkProtocol::SERVICE_AUTH;
    mpStrategy = nullptr;
}

HbNetworkProtocol::NetworkTypes HbServerAuthService::enabledNetworkTypes() const
{
    return HbNetworkProtocol::NETWORK_TCP |
           HbNetworkProtocol::NETWORK_SSL;
}

void HbServerAuthService::onContractReceived( const HbNetworkContract * contract )
{
    q_assert_ptr( mpStrategy );

    const HbAuthRequestContract * auth_request = contract->value< const HbAuthRequestContract >();
    if( auth_request )
    {
        if( mpStrategy->tryLogin( auth_request ) )
        {

        }
    }
}

void HbServerAuthService::onSocketConnected   ( sockuuid socket_uuid )
{

}

void HbServerAuthService::onSocketDisconnected( sockuuid socket_uuid )
{

}
