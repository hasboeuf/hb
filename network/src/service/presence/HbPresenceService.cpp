// Qt
// Hb
// Local
#include <service/presence/HbPresenceService.h>
#include <contract/presence/HbPresenceContract.h>
#include <contract/presence/HbPresenceStatusContract.h>

using namespace hb::network;

HbPresenceService::HbPresenceService()
{
}

HbNetworkProtocol::NetworkTypes HbPresenceService::enabledNetworkTypes() const
{
    return HbNetworkProtocol::NETWORK_TCP;
}

void HbPresenceService::plugContracts( HbNetworkExchanges & exchanges )
{
    exchanges.plug< HbPresenceContract >();
    exchanges.plug< HbPresenceStatusContract>();
}

serviceuid HbPresenceService::uid() const
{
    return HbNetworkProtocol::SERVICE_PRESENCE;
}
