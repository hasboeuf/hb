// Qt
// Hb
// Local
#include <service/channel/HbClientChannelService.h>

using namespace hb::network;

HbNetworkProtocol::NetworkTypes HbClientChannelService::enabledNetworkTypes() const
{
    return HbNetworkProtocol::NETWORK_TCP |
           HbNetworkProtocol::NETWORK_WEB |
           HbNetworkProtocol::NETWORK_SSL |
           HbNetworkProtocol::NETWORK_UDP |
           HbNetworkProtocol::NETWORK_LOCAL |
           HbNetworkProtocol::NETWORK_BLUETOOTH;
}

void HbClientChannelService::onContractReceived( const HbNetworkContract * contract )
{

}

