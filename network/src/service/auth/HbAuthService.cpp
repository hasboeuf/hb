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
}

void HbAuthService::plugContracts( HbNetworkExchanges & exchanges )
{
    exchanges.plug< HbAuthFacebookRequestContract >();
    exchanges.plug< HbAuthRequestContract >();
    exchanges.plug< HbAuthStatusContract >();
}

serviceuid HbAuthService::uid() const
{
    return HbNetworkProtocol::SERVICE_AUTH;
}
