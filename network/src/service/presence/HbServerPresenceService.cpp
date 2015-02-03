// Qt
// Hb
// Local
#include <service/presence/HbServerPresenceService.h>

using namespace hb::network;

HbServerPresenceService::HbServerPresenceService()
{
    mUuid = HbNetworkProtocol::SERVICE_PRESENCE;
}

HbNetworkProtocol::NetworkTypes HbServerPresenceService::enabledNetworkTypes() const
{
    return HbNetworkProtocol::NETWORK_TCP;
}

void HbServerPresenceService::onContractReceived( const HbNetworkContract * contract )
{

}

void HbServerPresenceService::onSocketConnected   ( sockuuid socket_uuid )
{

}

void HbServerPresenceService::onSocketDisconnected( sockuuid socket_uuid )
{

}
