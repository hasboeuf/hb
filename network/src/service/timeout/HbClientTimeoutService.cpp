// Qt
// Hb
// Local
#include <service/timeout/HbClientTimeoutService.h>

using namespace hb::network;

HbNetworkProtocol::NetworkTypes HbClientTimeoutService::enabledNetworkTypes() const
{
    return HbNetworkProtocol::NETWORK_TCP;
}

void HbClientTimeoutService::onContractReceived( const HbNetworkContract * contract )
{

}

