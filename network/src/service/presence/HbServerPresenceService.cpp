// Qt
// Hb
// Local
#include <service/presence/HbServerPresenceService.h>

using namespace hb::network;

HbServerPresenceService::HbServerPresenceService()
{
    mId = HbNetworkProtocol::SERVICE_PRESENCE;
}

HbNetworkProtocol::NetworkTypes HbServerPresenceService::enabledNetworkTypes() const
{
    return HbNetworkProtocol::NETWORK_TCP;
}

void HbServerPresenceService::onSocketConnected   ( sockuid socket_uid )
{

}

void HbServerPresenceService::onSocketDisconnected( sockuid socket_uid )
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
