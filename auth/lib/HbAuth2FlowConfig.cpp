// Local
#include <HbAuth2FlowConfig.h>

using namespace hb::auth;

void HbAuth2FlowConfig::setClientId(const QString& clientId) {
    mClientId = clientId;
}

QString HbAuth2FlowConfig::clientId() const {
    return mClientId;
}

void HbAuth2FlowConfig::setClientSecret(const QString& clientSecret) {
    mClientSecret = clientSecret;
}

QString HbAuth2FlowConfig::clientSecret() const {
    return mClientSecret;
}

void HbAuth2FlowConfig::setAuthorizationCode(const QString& authorizationCode) {
    mAuthorizationCode = authorizationCode;
}

QString HbAuth2FlowConfig::authorizationCode() const {
    return mAuthorizationCode;
}

void HbAuth2FlowConfig::setAccessToken(const QString& accessToken) {
    mAccessToken = accessToken;
}

QString HbAuth2FlowConfig::accessToken() const {
    return mAccessToken;
}

void HbAuth2FlowConfig::setRedirectUrl(const QUrl& url) {
    mRedirectUrl = url;
}

QUrl HbAuth2FlowConfig::redirectUrl() const {
    return mRedirectUrl;
}

quint16 HbAuth2FlowConfig::port() const {
    return mRedirectUrl.port();
}

bool HbAuth2FlowConfig::isSecure() const {
    return mRedirectUrl.scheme() == "https";
}

void HbAuth2FlowConfig::addScope(const QString& scope) {
    mScopes.append(scope);
}

QStringList HbAuth2FlowConfig::scopes() const {
    return mScopes;
}

namespace hb {
namespace auth {

QDataStream& operator<<(QDataStream& stream, const HbAuth2FlowConfig& config) {
    stream << config.mClientId << config.mClientSecret << config.mRedirectUrl << config.mScopes;
    return stream;
}

QDataStream& operator>>(QDataStream& stream, HbAuth2FlowConfig& config) {
    stream >> config.mClientId >> config.mClientSecret >> config.mRedirectUrl >> config.mScopes;
    return stream;
}

} // namespace auth
} // namespace hb
