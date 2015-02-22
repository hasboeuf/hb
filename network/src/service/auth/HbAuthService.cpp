// Qt
// Hb
// Local
#include <service/auth/HbAuthService.h>
#include <contract/auth/HbAuthFacebookRequestContract.h>
#include <contract/auth/HbAuthRequestContract.h>
#include <contract/auth/HbAuthStatusContract.h>


using namespace hb::network;

HbAuthService::HbAuthService()
{
    mId = HbNetworkProtocol::SERVICE_AUTH;
}

HbNetworkProtocol::NetworkTypes HbAuthService::enabledNetworkTypes() const
{
    return HbNetworkProtocol::NETWORK_TCP |
           HbNetworkProtocol::NETWORK_SSL;
}

void HbAuthService::plugContracts( HbNetworkExchanges & exchanges )
{
    exchanges.plug< HbAuthFacebookRequestContract >();
    exchanges.plug< HbAuthRequestContract >();
    exchanges.plug< HbAuthStatusContract >();
}
