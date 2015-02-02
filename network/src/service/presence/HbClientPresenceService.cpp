// Qt
// Hb
// Local
#include <service/presence/HbClientPresenceService.h>

using namespace hb::network;

HbNetworkProtocol::NetworkTypes HbClientPresenceService::enabledNetworkTypes() const
{
    return HbNetworkProtocol::NETWORK_TCP;
}

void HbClientPresenceService::onContractReceived( const HbNetworkContract * contract )
{

}

