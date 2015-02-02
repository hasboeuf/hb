// Qt
// Hb
// Local
#include <service/auth/HbClientAuthService.h>

using namespace hb::network;

HbNetworkProtocol::NetworkTypes HbClientAuthService::enabledNetworkTypes() const
{
    return HbNetworkProtocol::NETWORK_TCP |
           HbNetworkProtocol::NETWORK_SSL;
}

void HbClientAuthService::onContractReceived( const HbNetworkContract * contract )
{

}
