// Qt
#include <QtCore/QPair>
#include <QtCore/QUrlQuery>
// Hb
#include <HbLogService.h>
#include <core/HbDictionaryHelper.h>
// Local
#include <HbO2.h>

using namespace hb::link;

HbO2::HbO2(QObject* parent) : QObject(parent) {
    mLinkStatus = UNLINKED;
}

bool HbO2::isValid() const {
    if (mLinkStatus != UNLINKED) {
        qDebug() << "HbO2 already linked or in linking";
        return false;
    }

    if (!QUrl(mRedirectUri).isValid() || endPoint().isEmpty()) {
        qWarning() << "HbO2 not valid";
        return false;
    }

    return true;
}

QHash<QString, QString> HbO2::getUrlItems(const QString& content) {
    QUrl url(ENRICHED_URI_BASE + content);
    QUrlQuery response(url);

    return HbDictionaryHelper::toHash<QString, QString>(response.queryItems());
}

const QString& HbO2::errorString() const {
    return mErrorString;
}

HbO2::LinkStatus HbO2::linkStatus() const {
    return mLinkStatus;
}

const QString& HbO2::redirectUri() const {
    return mRedirectUri;
}

const QString& HbO2::code() const {
    return mCode;
}
