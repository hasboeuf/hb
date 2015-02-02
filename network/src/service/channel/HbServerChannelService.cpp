// Qt
// Hb
// Local
#include <service/channel/HbServerChannelService.h>

using namespace hb::network;

HbNetworkProtocol::NetworkTypes HbServerChannelService::enabledNetworkTypes() const
{
    return HbNetworkProtocol::NETWORK_TCP |
           HbNetworkProtocol::NETWORK_WEB |
           HbNetworkProtocol::NETWORK_SSL |
           HbNetworkProtocol::NETWORK_UDP |
           HbNetworkProtocol::NETWORK_LOCAL |
           HbNetworkProtocol::NETWORK_BLUETOOTH;
}

void HbServerChannelService::onContractReceived( const HbNetworkContract * contract )
{

}

void HbServerChannelService::onUserConnected   ( const HbNetworkUserInfo & user_info )
{

}

void HbServerChannelService::onUserDisconnected( const HbNetworkUserInfo & user_info )
{

}
