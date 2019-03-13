// Qt
#include <QtCore/QCoreApplication>
#include <QtCore/QCryptographicHash>
#include <QtCore/QDataStream>
#include <QtCore/QElapsedTimer>
#include <QtNetwork/QLocalServer>
#include <QtNetwork/QLocalSocket>
// Local
#include <core/HbSingleApplication.h>

using namespace hb::tools;

#include <QString>

static QString getServerName(const QString& applicationName) {
    return QCryptographicHash::hash(applicationName.toLocal8Bit(), QCryptographicHash::Md5).toHex();
}

HbSingleApplication::HbSingleApplication() {
    Q_ASSERT(!QCoreApplication::applicationName().isEmpty());
    mServerName = getServerName(QCoreApplication::applicationName());
}

HbSingleApplication::~HbSingleApplication() {
}

bool HbSingleApplication::connectToExistingApplication(int msTimeout) {
    Q_ASSERT(!mClient);
    mClient.reset(new QLocalSocket);
    mClient->connectToServer(mServerName, QLocalSocket::ReadWrite);
    if (!mClient->waitForConnected(msTimeout)) {
        mClient.reset();
        return false;
    }
    return true;
}

bool HbSingleApplication::acquireApplication() {
    Q_ASSERT(mMessageHandler);
    Q_ASSERT(!mServer);
    mServer.reset(new QLocalServer());
    QObject::connect(mServer.data(), &QLocalServer::newConnection, [this]() {
        QLocalSocket* socket = mServer->nextPendingConnection();
        QObject::connect(socket, &QLocalSocket::readyRead, [this, socket]() { readFromClientSocket(socket); });
    });

    mServer->removeServer(mServerName);
    return mServer->listen(mServerName);
}

QVariant HbSingleApplication::sendToExistingApplication(const QVariant& message, int msTimeout) {
    Q_ASSERT(mClient);
    Q_ASSERT(mClient->state() == QLocalSocket::ConnectedState);

    QDataStream stream(mClient.data());
    auto status = (stream << message).status();
    Q_ASSERT(status == QDataStream::Status::Ok);
    mClient->flush();

    QElapsedTimer timer;
    timer.start();
    while (mClient->bytesAvailable() == 0) {
        if (timer.elapsed() >= msTimeout) {
            return QVariant();
        }
        QCoreApplication::instance()->processEvents();
    }

    QVariant response;
    status = (stream >> response).status();
    Q_ASSERT(status == QDataStream::Status::Ok);
    return response;
}

void HbSingleApplication::setMessageHandlerFunction(MessageHandlerFunction handler) {
    Q_ASSERT(!mMessageHandler);
    mMessageHandler = handler;
}

void HbSingleApplication::readFromClientSocket(QLocalSocket* socket) {
    QDataStream stream(socket);
    QVariant message;
    auto status = (stream >> message).status();
    Q_ASSERT(status == QDataStream::Status::Ok);
    QVariant reply = mMessageHandler(message);
    status = (stream << reply).status();
    Q_ASSERT(status == QDataStream::Status::Ok);
    socket->flush();
    socket->close();
    socket->deleteLater();
}
