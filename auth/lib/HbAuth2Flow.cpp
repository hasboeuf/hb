// Qt
#include <QtCore/QByteArray>
#include <QtCore/QUrlQuery>
#include <QtNetwork/QNetworkRequest>
#include <QtNetworkAuth/QOAuthHttpServerReplyHandler>
// Hb
#include <core/HbStringHelper.h>
#include <network/HbWebServiceController.h>
#include <network/HbWebServiceJob.h>
#include <network/HbWebServiceResult.h>
// Local
#include <HbAuth2Flow.h>
#include <HbAuth2HttpReplyHandler.h>
#include <HbAuthConstants.h>

using namespace hb::tools;
using namespace hb::auth;

static AuthKeys AUTH_KEYS;

static QUrlQuery createQuery(const QVariantMap& parameters) {
    QUrlQuery query;
    for (auto it = parameters.begin(), end = parameters.end(); it != end; ++it)
        query.addQueryItem(it.key(), it.value().toString());
    return query;
}

HbAuth2Flow::HbAuth2Flow(QNetworkAccessManager* networkAccessManager, QObject* parent) :
        QAbstractOAuth2(networkAccessManager, parent),
        mReplyHandler(nullptr) {
    setResponseType(AUTH_KEYS.code);
    updateStatus();
}

void HbAuth2Flow::init(const HbAuth2FlowConfig& config) {
    if (mReplyHandler) {
        mReplyHandler->deleteLater();
        mReplyHandler = nullptr;
        setReplyHandler(mReplyHandler);
    }
    mConfig = config;
    setClientIdentifier(config.clientId());
    setClientIdentifierSharedKey(config.clientSecret());
    setScope(mConfig.scopes().join(mScopeSeparator));
    updateStatus();
}

HbAuth2FlowConfig HbAuth2Flow::config() const {
    return mConfig;
}

void HbAuth2Flow::setScopeSeparator(const QString& separator) {
    mScopeSeparator = separator;
}

QString HbAuth2Flow::authorizationCode() const {
    return mConfig.authorizationCode();
}

void HbAuth2Flow::setAccessTokenUrl(const QUrl& accessTokenUrl) {
    if (accessTokenUrl == mAccessTokenUrl) {
        return;
    }
    mAccessTokenUrl = accessTokenUrl;
}

QString HbAuth2Flow::accessToken() const {
    return config().accessToken();
}

void HbAuth2Flow::setAccessToken(const QString& accessToken) {
    mConfig.setAccessToken(accessToken);
    updateStatus();
}

void HbAuth2Flow::requestAuthorizationCode() {
    Q_ASSERT(!clientIdentifier().isEmpty());
    Q_ASSERT(!mReplyHandler);
    Q_ASSERT(authorizationUrl().isValid());

    mReplyHandler = new HbAuth2HttpReplyHandler(this);
    mReplyHandler->setRedirectUrl(mConfig.redirectUrl());
    mReplyHandler->init();
    Q_ASSERT(mReplyHandler->isReady());
    setReplyHandler(mReplyHandler);

    connect(mReplyHandler,
            &QOAuthHttpServerReplyHandler::callbackReceived,
            this,
            &HbAuth2Flow::onCallbackReceived,
            Qt::UniqueConnection);

    resourceOwnerAuthorization(authorizationUrl(), QVariantMap());
}

void HbAuth2Flow::requestAccessToken() {
    Q_ASSERT(status() >= Status::TemporaryCredentialsReceived);
    Q_ASSERT(!clientIdentifier().isEmpty());
    Q_ASSERT(!clientIdentifierSharedKey().isEmpty());
    Q_ASSERT(!mConfig.authorizationCode().isEmpty());
    Q_ASSERT(!mReplyHandler);

    mReplyHandler = new HbAuth2ReplyHandler(this);
    mReplyHandler->setRedirectUrl(mConfig.redirectUrl());
    mReplyHandler->init();
    Q_ASSERT(mReplyHandler->isReady());
    setReplyHandler(mReplyHandler);

    QVariantMap parameters;
    QNetworkRequest request(mAccessTokenUrl);
    QUrlQuery query;
    parameters.insert(AUTH_KEYS.grantType, QStringLiteral("authorization_code"));
    parameters.insert(AUTH_KEYS.code, QUrl::toPercentEncoding(mConfig.authorizationCode()));
    parameters.insert(AUTH_KEYS.redirectUri, QUrl::toPercentEncoding(callback()));
    parameters.insert(AUTH_KEYS.clientIdentifier, QUrl::toPercentEncoding(clientIdentifier()));
    parameters.insert(AUTH_KEYS.clientSharedSecret, clientIdentifierSharedKey());
    query = createQuery(parameters);
    request.setHeader(QNetworkRequest::ContentTypeHeader, QStringLiteral("application/x-www-form-urlencoded"));

    const QString data = query.toString(QUrl::FullyEncoded);

    qDebug() << mAccessTokenUrl << data;

    QNetworkReply* reply = networkAccessManager()->post(request, data.toUtf8());
    QObject::connect(
        reply, &QNetworkReply::finished, this, [this, reply] { mReplyHandler->networkReplyFinished(reply); });

    connect(mReplyHandler,
            &QOAuthHttpServerReplyHandler::tokensReceived,
            this,
            &HbAuth2Flow::onTokenReceived,
            Qt::UniqueConnection);
}

void HbAuth2Flow::grant() {
    Q_UNREACHABLE();
}

void HbAuth2Flow::updateStatus() {
    if (!mConfig.authorizationCode().isEmpty()) {
        if (!config().accessToken().isEmpty()) {
            setStatus(Status::Granted);
        } else {
            setStatus(Status::TemporaryCredentialsReceived);
        }
    } else {
        setStatus(Status::NotAuthenticated);
    }
}

void HbAuth2Flow::resourceOwnerAuthorization(const QUrl& url, const QVariantMap& parameters) {
    const QUrl u = buildAuthenticateUrl(parameters);
    emit authorizeWithBrowser(u);
}

void HbAuth2Flow::onCallbackReceived(const QVariantMap& values) {
    Q_ASSERT(mReplyHandler);
    mReplyHandler->deleteLater();
    mReplyHandler = nullptr;
    setReplyHandler(nullptr);

    if (status() == Status::NotAuthenticated) {
        handleAuthorizationResponse(values);
        return;
    }

    if (status() == Status::TemporaryCredentialsReceived) {
        handleAccessTokenResponse(values);
        return;
    }

    qCritical() << "Unexpected call";
}

void HbAuth2Flow::onTokenReceived(const QVariantMap& values) {
    handleAccessTokenResponse(values);
}

void HbAuth2Flow::handleAuthorizationResponse(const QVariantMap& values) {
    const QString error = values.value(AUTH_KEYS.error).toString();
    const QString code = values.value(AUTH_KEYS.code).toString();
    const QString receivedState = values.value(AUTH_KEYS.state).toString();

    if (error.size()) {
        const QString uri = values.value(AUTH_KEYS.errorUri).toString();
        const QString description = values.value(AUTH_KEYS.errorDescription).toString();
        qWarning() << "Authorization error:" << error << description << uri;
        requestFailed(Error::OAuthCallbackNotVerified);
        return;
    }

    if (code.isEmpty()) {
        qWarning() << "Authorization code not received";
        requestFailed(Error::OAuthCallbackNotVerified);
        return;
    }

    if (receivedState.isEmpty()) {
        qWarning() << "State not received";
        requestFailed(Error::OAuthCallbackNotVerified);
        return;
    }

    if (state() != receivedState) {
        qWarning() << "State mismatch";
        requestFailed(Error::OAuthCallbackNotVerified);
        return;
    }

    mConfig.setAuthorizationCode(code);
    updateStatus();
}

void HbAuth2Flow::handleAccessTokenResponse(const QVariantMap& values) {
    if (values.contains(AUTH_KEYS.error)) {
        qWarning() << "Access token error" << values.value(AUTH_KEYS.error).toString();
        requestFailed(Error::OAuthTokenNotFoundError);
        return;
    }

    bool ok;
    const QString accessToken = values.value(AUTH_KEYS.accessToken).toString();
    const QString tokenType = values.value(AUTH_KEYS.tokenType).toString();
    int expiresIn = values.value(AUTH_KEYS.expiresIn).toInt(&ok);
    if (!ok)
        expiresIn = -1;
    QString refreshToken = values.value(AUTH_KEYS.refreshToken).toString();
    QString scope = values.value(AUTH_KEYS.scope).toString();
    if (accessToken.isEmpty()) {
        qWarning() << "Access token not received";
        requestFailed(Error::OAuthTokenNotFoundError);
        return;
    }

    setAccessToken(accessToken);
}

QUrl HbAuth2Flow::buildAuthenticateUrl(const QVariantMap& parameters) {
    const QString stateE = HbStringHelper::randomString(8);
    setState(stateE);

    QVariantMap p(parameters);
    QUrl url(authorizationUrl());

    p.insert(AUTH_KEYS.responseType, responseType());
    p.insert(AUTH_KEYS.clientIdentifier, clientIdentifier());
    p.insert(AUTH_KEYS.redirectUri, callback());
    p.insert(AUTH_KEYS.scope, scope());
    p.insert(AUTH_KEYS.state, state());
    url.setQuery(createQuery(p));
    qDebug("Generated URL: %s", qPrintable(url.toString()));
    return url;
}
