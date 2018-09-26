// Qt
#include <QtCore/QTimer>
// Local
#include <mock/MockNetwork.h>

MockNetworkReply::MockNetworkReply(const QByteArray data, Error error, QObject* parent) : QNetworkReply(parent) {
    open(QIODevice::ReadOnly);

    mData = data;
    mNetworkError = QNetworkReply::NoError;
    int httpCode = 0;

    switch (error) {
    case HTTP200:
        httpCode = 200;
        break;
    case HTTP301:
        httpCode = 301;
        setAttribute(QNetworkRequest::RedirectionTargetAttribute, "url");
        break;
    case HTTP400:
        httpCode = 400;
        mNetworkError = QNetworkReply::ProtocolInvalidOperationError;
        break;
    case HTTP401:
        httpCode = 401;
        mNetworkError = QNetworkReply::AuthenticationRequiredError;
        break;
    case HTTP403:
        httpCode = 403;
        mNetworkError = QNetworkReply::ContentAccessDenied;
        break;
    case HTTP404:
        httpCode = 404;
        mNetworkError = QNetworkReply::ContentNotFoundError;
        break;
    case HTTP405:
        httpCode = 405;
        mNetworkError = QNetworkReply::ContentOperationNotPermittedError;
        break;
    case HTTP407:
        httpCode = 407;
        mNetworkError = QNetworkReply::ProxyAuthenticationRequiredError;
        break;
    case HTTP409:
        httpCode = 409;
        mNetworkError = QNetworkReply::ContentConflictError;
        break;
    case HTTP410:
        httpCode = 410;
        mNetworkError = QNetworkReply::ContentGoneError;
        break;
    case HTTP418:
        httpCode = 418;
        mNetworkError = QNetworkReply::ProtocolInvalidOperationError;
        break;
    case HTTP500:
        httpCode = 500;
        mNetworkError = QNetworkReply::InternalServerError;
        break;
    case HTTP501:
        httpCode = 501;
        mNetworkError = QNetworkReply::OperationNotImplementedError;
        break;
    case HTTP503:
        httpCode = 503;
        mNetworkError = QNetworkReply::ServiceUnavailableError;
        break;
    case ConnectionRefused:
        mNetworkError = QNetworkReply::ConnectionRefusedError;
        break;
    case Timeout:
        mNetworkError = QNetworkReply::TimeoutError;
        break;
    default:
        Q_UNREACHABLE();
    }

    setAttribute(QNetworkRequest::HttpStatusCodeAttribute, httpCode);
}

void MockNetworkReply::abort() {
    mNetworkError = QNetworkReply::NetworkError::OperationCanceledError;
    setAttribute(QNetworkRequest::HttpStatusCodeAttribute, 0);
    mData.clear();
    QTimer::singleShot(0, this, &MockNetworkReply::onFinished);
}

void MockNetworkReply::start() {
    QTimer::singleShot(100, this, &MockNetworkReply::onFinished);
}

qint64 MockNetworkReply::readData(char* data, qint64 maxLen) {
    QByteArray bytes = mData.mid(mDataIndex, maxLen);
    memcpy(data, bytes.data(), bytes.length());
    mDataIndex += bytes.length();
    return bytes.length();
}

qint64 MockNetworkReply::writeData(const char* data, qint64 maxSize) {
    Q_UNUSED(data);
    Q_UNUSED(maxSize);
    return -1;
}

qint64 MockNetworkReply::bytesAvailable() const {
    return -1;
}

void MockNetworkReply::onFinished() {
    if (mNetworkError != QNetworkReply::NoError) {
        setError(mNetworkError, "not set in mock");
        emit QNetworkReply::error(mNetworkError);
    }
    emit QNetworkReply::finished();
}

QNetworkReply*
MockNetworkAccessManager::createRequest(Operation operation, const QNetworkRequest& request, QIODevice* outgoingData) {
    Q_ASSERT(!mReplies.isEmpty());
    auto reply = mReplies.dequeue();
    reply->start();
    return reply;
}

void MockNetworkAccessManager::enqueue(MockNetworkReply* reply) {
    mReplies.enqueue(reply);
}
