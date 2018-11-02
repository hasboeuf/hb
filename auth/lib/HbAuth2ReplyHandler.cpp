// Qt
// Local
#include <HbAuth2ReplyHandler.h>

using namespace hb::auth;

HbAuth2ReplyHandler::HbAuth2ReplyHandler(QObject* parent) : QOAuthOobReplyHandler(parent) {
}

QString HbAuth2ReplyHandler::callback() const {
    return mRedirectUrl.toString(QUrl::EncodeDelimiters);
}

void HbAuth2ReplyHandler::init() {
    // Default implementation
}

bool HbAuth2ReplyHandler::isReady() const {
    return true; // Default implementation
}

quint16 HbAuth2ReplyHandler::port() const {
    return mRedirectUrl.port();
}

bool HbAuth2ReplyHandler::isSecure() const {
    return mRedirectUrl.scheme() == "https";
}

void HbAuth2ReplyHandler::setRedirectUrl(const QUrl& redirectUri) {
    mRedirectUrl = redirectUri;
}

QUrl HbAuth2ReplyHandler::redirectUrl() const {
    return mRedirectUrl;
}
