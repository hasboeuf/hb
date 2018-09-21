// Qt
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QUrlQuery>
#include <QtGui/QDesktopServices>
// Hb
#include <HbLogService.h>
#include <core/HbDictionaryHelper.h>
// Local
#include <google/HbO2ServerGoogle.h>

const QUrl HbO2ServerGoogle::endPoint() const {
    return QUrl(QStringLiteral("https://www.googleapis.com/oauth2/v4/token"));
}

const QHash<QString, QString> HbO2ServerGoogle::tokenRequest() const {
    QHash<QString, QString> request;
    request.insert(OAUTH2_CLIENT_ID, mConfig.clientId());
    request.insert(OAUTH2_CLIENT_SECRET, mConfig.clientSecret());
    request.insert(OAUTH2_CODE, mCode);
    request.insert(OAUTH2_REDIRECT_URI, mRedirectUri);
    request.insert(OAUTH2_GRANT_TYPE, GL_GRANT_TYPE_VALUE);

    return request;
}

HbO2::LinkStatus HbO2ServerGoogle::tokenResponse(const QByteArray& data) {
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull()) {
        qWarning() << "Null JSON document";
    }
    QJsonObject root(doc.object());

    if (root.contains(OAUTH2_ACCESS_TOKEN)) {
        mToken = root.value(OAUTH2_ACCESS_TOKEN).toString();
        mTokenExpiration = root.value(OAUTH2_EXPIRES_IN).toInt();

        return LINKED;
    } else {
        mErrorString += "undefined error";
        return UNLINKED;
    }
}
