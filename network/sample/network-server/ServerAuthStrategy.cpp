// Qt
// Hb
#include <service/auth/HbAuthService.h>
// Local
#include <ServerAuthStrategy.h>

using namespace hb::network;
using namespace hb::networkexample;

void ServerAuthStrategy::reset() {
}

bool ServerAuthStrategy::checkLogin(const HbAuthRequestContract* contract) {
    Q_UNUSED(contract)
    return true;
}

authstgy ServerAuthStrategy::type() const {
    return HbAuthService::AUTH_USER + 0;
}
