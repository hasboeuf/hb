// System
#include <iostream>
// Qt
#include <QtCore/QJsonDocument>
// Local
#include <network/HbWebServiceResult.h>

using namespace hb::tools;

int HbWebServiceResult::httpStatusCode() const {
    return mHttpStatusCode;
}

QList<QNetworkReply::RawHeaderPair> HbWebServiceResult::rawHeadersPair() const {
    return mRawHeadersPair;
}

QNetworkReply::NetworkError HbWebServiceResult::networkError() const {
    return mNetworkError;
}

QString HbWebServiceResult::networkErrorString() const {
    return mNetworkErrorString;
}

QByteArray HbWebServiceResult::rawContent() const {
    return mContent;
}

QJsonDocument HbWebServiceResult::jsonContent() const {
    QJsonParseError parseError;
    QJsonDocument jsonReply = QJsonDocument::fromJson(mContent, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        std::cerr << "Failed to parse HTTP content as json\n" << qUtf8Printable(mContent.left(100));
    }
    return jsonReply;
}
