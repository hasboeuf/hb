// Hb
#include <HbLogService.h>
#include <HbO2Server.h>
// Local
#include <contract/auth/HbOAuthRequestContract.h>
#include <service/auth/HbAuthService.h>
#include <service/auth/HbServerOAuthStrategy.h>
#ifdef DEV
#include <mock/HbNetworkUserInfoMock.h>
#endif

using namespace hb::network;
using namespace hb::link;

HbServerOAuthStrategy::HbServerOAuthStrategy() : HbServerAuthStrategy() {
}

HbServerOAuthStrategy::~HbServerOAuthStrategy() {
    reset();
}

void HbServerOAuthStrategy::reset() {
    qDeleteAll(mPendingToken.keys());
    mPendingToken.clear();
    mPendingRequest.clear();
}

void HbServerOAuthStrategy::setConfig(const HbO2ServerConfig& config) {
    mConfig = config;
}

void HbServerOAuthStrategy::onLinkFailed(const QString& error) {
    HbO2Server* server_auth = dynamic_cast<HbO2Server*>(sender());
    Q_ASSERT(server_auth);
    Q_ASSERT(mPendingToken.contains(server_auth));

    qDebug() << "Server link failed for user" << server_auth->config().clientId() << error;

    networkuid sender = mPendingToken.take(server_auth);

    server_auth->deleteLater();

    emit authFailed(sender, HbNetworkProtocol::AUTH_OAUTH_KO, error);
}
