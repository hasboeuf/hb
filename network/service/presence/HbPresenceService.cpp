// Qt
// Hb
// Local
#include <service/presence/HbPresenceService.h>
#include <contract/presence/HbPresenceContract.h>

using namespace hb::network;

HbPresenceService::HbPresenceService()
{
}

void HbPresenceService::plugContracts( HbNetworkExchanges & exchanges )
{
    exchanges.plug< HbPresenceContract >();
}

serviceuid HbPresenceService::uid() const
{
    return HbNetworkProtocol::SERVICE_PRESENCE;
}
