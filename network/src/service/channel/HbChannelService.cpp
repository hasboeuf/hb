// Qt
// Hb
// Local
#include <service/channel/HbChannelService.h>

using namespace hb::network;

HbChannelService::HbChannelService()
{
    mId = HbNetworkProtocol::SERVICE_CHANNEL;
}

HbNetworkProtocol::NetworkTypes HbChannelService::enabledNetworkTypes() const
{
    return HbNetworkProtocol::NETWORK_TCP |
           HbNetworkProtocol::NETWORK_WEB |
           HbNetworkProtocol::NETWORK_SSL |
           HbNetworkProtocol::NETWORK_UDP |
           HbNetworkProtocol::NETWORK_LOCAL |
           HbNetworkProtocol::NETWORK_BLUETOOTH;
}

void HbChannelService::plugContracts( HbNetworkExchanges & exchanges )
{
    Q_UNUSED( exchanges )
}
