// Qt
#include <QtCore/QPair>
#include <QtCore/QUrlQuery>
// Local
#include <HbGlobal.h>
#include <network/HbHttpRequester.h>

using namespace hb::tools;

HbHttpRequester::HbHttpRequester(QObject* parent) : QObject(parent) {
}

HbHttpRequester::~HbHttpRequester() {
}

quint64 HbHttpRequester::processRequest(const QUrl& url, quint32 timeout) {
    QNetworkRequest request(url);
    QNetworkReply* reply = mManager.get(request);

    quint64 id = mReplies.add(reply, timeout);
    if (id > 0) {
        connect(reply, &QNetworkReply::finished, this, &HbHttpRequester::onFinished, Qt::UniqueConnection);
        connect(reply,
                (void (QNetworkReply::*)(QNetworkReply::NetworkError))(&QNetworkReply::error),
                this,
                &HbHttpRequester::onError,
                Qt::UniqueConnection);
    }

    return id;
}

void HbHttpRequester::onFinished() {
    QNetworkReply* reply = dynamic_cast<QNetworkReply*>(sender());
    Q_ASSERT(reply);

    quint64 id = mReplies.id(reply);
    mReplies.remove(reply);

    if (reply->error() == QNetworkReply::NoError) {
        QString data(reply->readAll());
        QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());

        emit requestFinished(id, doc);
    } else {
        emit requestError(id, reply->errorString());
    }

    reply->deleteLater();
}

void HbHttpRequester::onError(const QNetworkReply::NetworkError& error) {
    Q_UNUSED(error)

    QNetworkReply* reply = dynamic_cast<QNetworkReply*>(sender());
    Q_ASSERT(reply);

    quint64 id = mReplies.id(reply);

    emit requestError(id, reply->errorString());

    reply->deleteLater();
}
