#ifndef HBAUTH2FLOW_H
#define HBAUTH2FLOW_H

// Qt
#include <QtNetworkAuth/QOAuth2AuthorizationCodeFlow>
// Local
#include <HbAuth2FlowConfig.h>

namespace hb {
namespace auth {
class HbAuth2HttpReplyHandler;
class HbAuth2ReplyHandler;

class HbAuth2Flow : public QAbstractOAuth2 {
    Q_OBJECT
public:
    HbAuth2Flow(QNetworkAccessManager* networkAccessManager, QObject* parent = nullptr);

    void init(const HbAuth2FlowConfig& config);

    HbAuth2FlowConfig config() const;

    void setScopeSeparator(const QString& separator);

    QString authorizationCode() const;
    QString accessToken() const;

    void setAccessTokenUrl(const QUrl& accessTokenUrl);

    void requestAuthorizationCode();
    void requestAccessToken();

signals:
    void authorized();

protected:
    void setAccessToken(const QString& accessToken);
    void resourceOwnerAuthorization(const QUrl& url, const QVariantMap& parameters) override;

private:
    void grant() override;
    void updateStatus();
    void onCallbackReceived(const QVariantMap& values);
    void onTokenReceived(const QVariantMap& values);
    void handleAuthorizationResponse(const QVariantMap& values);
    void handleAccessTokenResponse(const QVariantMap& values);
    QUrl buildAuthenticateUrl(const QVariantMap& parameters);

    HbAuth2ReplyHandler* mReplyHandler;
    QUrl mAccessTokenUrl;
    HbAuth2FlowConfig mConfig;
    QString mScopeSeparator = ",";
};
} // namespace auth
} // namespace hb
#endif // HBAUTH2FLOW_H
