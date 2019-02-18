#ifndef HBHTTPREQUESTER_H
#define HBHTTPREQUESTER_H

/*! \file HbHttpRequester.h */

// Qt
#include <QtCore/QJsonDocument>
#include <QtNetwork/QNetworkAccessManager>
// Local
#include <HbTools.h>
#include <network/HbTimeoutNetworkReplies.h>

namespace hb {
namespace tools {
/*!
 * HbHttpRequester makes HTTP request.
 * As an HTTP request is not a synchrone event,
 * it tracks a request, waits for the answer and
 * notifies when the associated response is received.
 * \sa HbTimeoutNetworkReplies
 */
class HB_TOOLS_DECL HbHttpRequester : public QObject {
    Q_OBJECT

public:
    HbHttpRequester(QObject* parent = nullptr);
    virtual ~HbHttpRequester();

    quint64 processRequest(const QUrl& url, quint32 timeout = hb::tools::HbTimeoutNetworkReply::msDefaultTimeout);

    void onFinished();
    void onError(const QNetworkReply::NetworkError& error);

signals:
    void requestFinished(quint64 request_id, const QJsonDocument& response);
    void requestError(quint64 request_id, const QString& error);

private:
    QNetworkAccessManager mManager;
    HbTimeoutNetworkReplies mReplies;
};
} // namespace tools
} // namespace hb

using hb::tools::HbHttpRequester;

#endif // HbHttpRequester_H
