// Qt
// Hb
// Local
#include <contract/presence/HbPresenceContract.h>
#include <service/presence/HbPresenceService.h>

using namespace hb::network;

HbPresenceService::HbPresenceService() {
}

void HbPresenceService::plugContracts(HbNetworkExchanges& exchanges) {
    exchanges.plug<HbPresenceContract>();
}

serviceuid HbPresenceService::uid() const {
    return HbNetworkProtocol::SERVICE_PRESENCE;
}
