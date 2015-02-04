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

void HbServerPresenceService::onSocketConnected   ( sockuuid socket_uuid )
{

}

void HbServerPresenceService::onSocketDisconnected( sockuuid socket_uuid )
{

}

void HbServerPresenceService::onUserConnected   ( const HbNetworkUserInfo & user_info )
{

}

void HbServerPresenceService::onUserDisconnected( const HbNetworkUserInfo & user_info )
{

}

void HbServerPresenceService::onContractReceived( const HbNetworkContract * contract )
{

}
