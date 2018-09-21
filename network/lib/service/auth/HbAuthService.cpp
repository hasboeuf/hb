// Qt
// Hb
// Local
#include <contract/auth/HbAuthStatusContract.h>
#include <contract/auth/HbOAuthRequestContract.h>
#include <service/auth/HbAuthService.h>

using namespace hb::network;

HbAuthService::HbAuthService() {
}

void HbAuthService::plugContracts(HbNetworkExchanges& exchanges) {
    exchanges.plug<HbOAuthRequestContract>();
    exchanges.plug<HbAuthRequestContract>();
    exchanges.plug<HbAuthStatusContract>();
}

serviceuid HbAuthService::uid() const {
    return HbNetworkProtocol::SERVICE_AUTH;
}
