#ifndef HBAUTH2FLOWCONFIG_H
#define HBAUTH2FLOWCONFIG_H

/*! \file HbAuth2FlowConfig.h */

// Qt
// Hb
#include <QtCore/QDataStream>
#include <QtCore/QStringList>
#include <QtCore/QUrl>
// Local
#include <HbAuth.h>

namespace hb {
namespace auth {

class HB_AUTH_DECL HbAuth2FlowConfig {
    friend QDataStream& operator<<(QDataStream& stream, const HbAuth2FlowConfig& config);
    friend QDataStream& operator>>(QDataStream& stream, HbAuth2FlowConfig& config);

public:
    HbAuth2FlowConfig() = default;

    void setClientId(const QString& clientId);
    QString clientId() const;
    void setClientSecret(const QString& clientSecret);
    QString clientSecret() const;
    void setAuthorizationCode(const QString& authorizationCode);
    QString authorizationCode() const;
    void setAccessToken(const QString& accessToken);
    QString accessToken() const;
    void setRedirectUrl(const QUrl& url);
    QUrl redirectUrl() const;
    quint16 port() const;
    bool isSecure() const;
    void addScope(const QString& scope);
    QStringList scopes() const;

private:
    QString mClientId;
    QString mClientSecret;
    QUrl mRedirectUrl;
    QStringList mScopes;
    QString mAuthorizationCode;
    QString mAccessToken;
};

QDataStream& operator<<(QDataStream& stream, const HbAuth2FlowConfig& config);
QDataStream& operator>>(QDataStream& stream, HbAuth2FlowConfig& config);

} // namespace auth
} // namespace hb

#endif // HBAUTH2FLOWCONFIG_H
