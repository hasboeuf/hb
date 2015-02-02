// Qt
// Hb
// Local
#include <service/timeout/HbServerTimeoutService.h>

using namespace hb::network;

HbNetworkProtocol::NetworkTypes HbServerTimeoutService::enabledNetworkTypes() const
{
    return HbNetworkProtocol::NETWORK_TCP;
}

void HbServerTimeoutService::onContractReceived( const HbNetworkContract * contract )
{

}

void HbServerTimeoutService::onSocketConnected   ( sockuuid socket_uuid )
{

}

void HbServerTimeoutService::onSocketDisconnected( sockuuid socket_uuid )
{

}
