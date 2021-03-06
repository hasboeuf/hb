#ifndef HBWEBSERVICERESULT_H
#define HBWEBSERVICERESULT_H

/*! \file HbWebServiceResult.h */

// Qt
#include <QtCore/QMetaObject>
#include <QtNetwork/QNetworkReply>
// Local
#include <HbTools.h>

class TestHbWebServiceResult;

namespace hb {
namespace tools {
class HbWebServiceController;
/*!
 * Plain data struct representing result of a HbWebServiceJob
 */
struct HB_TOOLS_DECL HbWebServiceResult {
    friend HbWebServiceController;
    friend TestHbWebServiceResult;

public:
    int httpStatusCode() const;
    QList<QNetworkReply::RawHeaderPair> rawHeadersPair() const;
    QNetworkReply::NetworkError networkError() const;
    QString networkErrorString() const;
    QByteArray rawContent() const;
    QJsonDocument jsonContent() const;

private:
    int mHttpStatusCode = 0;
    QList<QNetworkReply::RawHeaderPair> mRawHeadersPair;
    QNetworkReply::NetworkError mNetworkError = QNetworkReply::NoError;
    QString mNetworkErrorString;
    QByteArray mContent;
};
} // namespace tools
} // namespace hb

#endif // HBWEBSERVICERESULT_H
