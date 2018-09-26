// System
#include <iostream>
// Qt
#include <QtCore/QTimer>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
// Local
#include <network/HbWebServiceController.h>
#include <network/HbWebServiceJob.h>
#include <network/HbWebServiceResult.h>

using namespace hb::tools;

static constexpr char TIMEOUT_PROPERTY[] = "timeoutReached";

static void setTypeHeader(QNetworkRequest* request, const QString typeHeader) {
    request->setHeader(QNetworkRequest::ContentTypeHeader, typeHeader);
}

static void useRawTypeHeader(QNetworkRequest* request) {
    setTypeHeader(request, "application/x-www-form-urlencoded");
}

static void useJsonTypeHeader(QNetworkRequest* request) {
    setTypeHeader(request, "application/json");
}

static void setUserAgent(QNetworkRequest* request, const QString& userAgent) {
    request->setHeader(QNetworkRequest::UserAgentHeader, userAgent);
}

static bool hasTimeout(const QNetworkReply& reply) {
    return reply.error() == QNetworkReply::NetworkError::TimeoutError || reply.property(TIMEOUT_PROPERTY).toBool();
}

HbWebServiceController::HbWebServiceController(QNetworkAccessManager* networkAccessManager, QObject* parent) :
        QObject(parent),
        mNetworkAccessManager(networkAccessManager) {
    Q_ASSERT(mNetworkAccessManager);
}

HbWebServiceJob* HbWebServiceController::get(const QUrl& url, int retries, int timeout) {
    QNetworkRequest request(url);
    useRawTypeHeader(&request);

    HbWebServiceJob* job = new HbWebServiceJob(this);
    call(
        [=]() {
            std::cout << "GET " << qUtf8Printable(request.url().toString()) << std::endl;
            return mNetworkAccessManager->get(request);
        },
        job,
        retries,
        timeout);

    return job;
}

void HbWebServiceController::call(std::function<QNetworkReply*()> webServiceCall,
                                  HbWebServiceJob* webServiceJob,
                                  int retries,
                                  int timeout) {
    QNetworkReply* networkReply = webServiceCall();
    Q_ASSERT(networkReply);

    connect(networkReply, &QNetworkReply::downloadProgress, webServiceJob, &HbWebServiceJob::downloadProgress);
    connect(networkReply, &QNetworkReply::uploadProgress, webServiceJob, &HbWebServiceJob::uploadProgress);

    connect(networkReply,
            &QNetworkReply::finished,
            this,
            [this, webServiceJob, networkReply, webServiceCall, retries, timeout]() {
                onCallFinished(webServiceJob, networkReply, webServiceCall, retries, timeout);
            });

    connect(webServiceJob, &HbWebServiceJob::cancelRequested, networkReply, &QNetworkReply::abort);

    if (timeout < 0) {
        return;
    }

    QTimer::singleShot(timeout, networkReply, [networkReply]() {
        if (networkReply->isRunning()) {
            networkReply->setProperty(TIMEOUT_PROPERTY, true);
            networkReply->abort();
        }
    });
}

void HbWebServiceController::onCallFinished(HbWebServiceJob* webServiceJob,
                                            QNetworkReply* networkReply,
                                            std::function<QNetworkReply*()> webServiceCall,
                                            int retries,
                                            int timeout) {
    networkReply->deleteLater();

    if (hasTimeout(*networkReply)) {
        if (retries > 0) {
            std::cerr << "Timeout occured on " << qUtf8Printable(networkReply->url().toString()) << " expect "
                      << retries << (retries == 1 ? " retry" : " retries") << std::endl;
            call(webServiceCall, webServiceJob, --retries, timeout);
            return;
        }
    }

    webServiceJob->setResult(resultForReply(networkReply));
}

HbWebServiceResult HbWebServiceController::resultForReply(QNetworkReply* reply) {
    HbWebServiceResult result;
    result.mHttpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    result.mRawHeadersPair = reply->rawHeaderPairs();
    result.mNetworkError = reply->error();
    result.mNetworkErrorString = reply->errorString();
    if (hasTimeout(*reply)) {
        result.mNetworkError = QNetworkReply::NetworkError::TimeoutError;
        result.mNetworkErrorString = "Operation timed out";
    }

    QByteArray content = reply->isReadable() ? reply->readAll() : QByteArray();
    result.mContent = content;
    return result;
}
