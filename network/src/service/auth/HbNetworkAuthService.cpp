// Qt
// Hb
// Local
#include <service/auth/HbServerAuthService.h>

using namespace hb::network;

HbServerAuthService::HbServerAuthService()
{
    mUuid = HbNetworkProtocol::SERVICE_AUTH;
}

HbNetworkProtocol::NetworkTypes HbServerAuthService::enabledNetworkTypes() const
{
    return HbNetworkProtocol::NETWORK_TCP |
           HbNetworkProtocol::NETWORK_SSL;
}

void HbServerAuthService::onContractReceived( const HbNetworkContract * contract )
{

}

void HbServerAuthService::onSocketConnected   ( sockuuid socket_uuid )
{

}

void HbServerAuthService::onSocketDisconnected( sockuuid socket_uuid )
{

}
