// Qt
#include <QtCore/QFile>
#include <QtCore/QUrl>
#include <QtNetwork/QSslKey>
#include <QtNetwork/QSslSocket>
#include <QtNetwork/QTcpSocket>
// Local
#include <HbAuthHttpServer.h>

using namespace hb::auth;

HbAuthHttpServer::HbAuthHttpServer(quint16 port, bool sslEnabled, QObject* parent) :
        QTcpServer(parent),
        mPort(port),
        mSslEnabled(sslEnabled) {
    QFile certFile(":/localhost.cert");
    QFile keyFile(":/localhost.key");
    certFile.open(QIODevice::ReadOnly);
    keyFile.open(QIODevice::ReadOnly);
    QSslCertificate certificate(&certFile, QSsl::Pem);
    QSslKey sslKey(&keyFile, QSsl::Rsa, QSsl::Pem);
    certFile.close();
    keyFile.close();

    Q_ASSERT(!certificate.isNull());
    Q_ASSERT(!sslKey.isNull());

    mSslConfiguration.setPeerVerifyMode(QSslSocket::VerifyNone);
    mSslConfiguration.setLocalCertificate(certificate);
    mSslConfiguration.setPrivateKey(sslKey);
    mSslConfiguration.setProtocol(QSsl::TlsV1SslV3);

    connect(this, &HbAuthHttpServer::newConnection, this, &HbAuthHttpServer::onNewConnection);
}

void HbAuthHttpServer::incomingConnection(qintptr handle) {
    QTcpSocket* socket = nullptr;

    if (mSslEnabled) {
        auto sslSocket = new QSslSocket(this);
        socket = sslSocket;
    } else {
        socket = new QTcpSocket(this);
    }

    if (socket->setSocketDescriptor(handle)) {
        addPendingConnection(socket);
        return;
    }
    delete socket;
}

void HbAuthHttpServer::onNewConnection() {
    auto socket = nextPendingConnection();

    connect(
        socket, QOverload<QTcpSocket::SocketError>::of(&QTcpSocket::error), this, [](QTcpSocket::SocketError error) {
            if (error != QTcpSocket::RemoteHostClosedError) {
                qWarning() << "Socket error" << error;
            }
        });

    if (QSslSocket* sslSocket = qobject_cast<QSslSocket*>(socket)) {
        connect(sslSocket,
                QOverload<const QList<QSslError>&>::of(&QSslSocket::sslErrors),
                this,
                [](const QList<QSslError>& sslErrors) { qWarning() << "Ssl errors" << sslErrors; });

        connect(sslSocket, &QSslSocket::encrypted, this, [this, socket]() { emit socketConnected(socket); });

        sslSocket->setSslConfiguration(mSslConfiguration);
        sslSocket->startServerEncryption();
    } else {
        emit socketConnected(socket);
    }
}
