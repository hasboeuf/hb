// Qt
#include <QtNetwork/QTcpSocket>
// Hb
#include <HbLogService.h>
// Local
#include <com/tcp/HbTcpClient.h>
#include <com/tcp/HbTcpSocket.h>

using namespace hb::network;

HbTcpClient::HbTcpClient(QObject* parent) : HbAbstractClient(parent) {
    mpSocket = nullptr;
}

HbTcpClient::~HbTcpClient() {
    leave();
}

bool HbTcpClient::join(const HbTcpClientConfig& config) {
    if (setConfiguration(config)) {
        return HbAbstractClient::join();
    }

    return false;
}

networkuid HbTcpClient::uid() const {
    if (mpSocket) {
        return mpSocket->uid();
    } else {
        return 0;
    }
}

HbNetworkProtocol::NetworkType HbTcpClient::type() const {
    if (mpSocket) {
        return mpSocket->type();
    } else {
        return HbNetworkProtocol::NETWORK_UNDEFINED;
    }
}

bool HbTcpClient::setConfiguration(const HbTcpClientConfig& config) {
    if (mpSocket) {
        qWarning() << "Can not apply configuration on instanciated socket";
        return false;
    }

    mConfig = config;
    return true;
}

const HbTcpClientConfig& HbTcpClient::configuration() const {
    return mConfig;
}

bool HbTcpClient::connectToNetwork() {
    Q_ASSERT(mpSocket);
    if (!mpSocket->connectToHost(this->configuration())) {
        qWarning() << "Can not connect to host";
        return false;
    }

    return true;
}

void HbTcpClient::disconnectFromNetwork() {
    Q_ASSERT(mpSocket);
    if (!mpSocket->leave()) {
        qWarning() << "Can not disconnect from host";
    } else {
        deleteSocket();
    }
}

void HbTcpClient::deleteSocket() {
    mpSocket->disconnect();
    mpSocket->deleteLater();
    mpSocket = nullptr;
}

HbAbstractSocket* HbTcpClient::pendingConnection() {
    if (mpSocket) {
        return mpSocket;
    }

    QTcpSocket* device = q_check_ptr(new QTcpSocket(this));
    mpSocket = q_check_ptr(new HbTcpSocket(device));

    connect(mpSocket,
            &HbAbstractSocket::socketError,
            this,
            [this]() { emit socketError(mpSocket->error(), mpSocket->errorString()); },
            Qt::UniqueConnection);

    HbTcpConfig::SocketOptions options = mConfig.options();

    mpSocket->setSocketOption(QAbstractSocket::LowDelayOption, options.testFlag(HbTcpConfig::SocketOption::LowDelay));
    mpSocket->setSocketOption(QAbstractSocket::KeepAliveOption, options.testFlag(HbTcpConfig::SocketOption::KeepAlive));
    mpSocket->setSocketOption(QAbstractSocket::MulticastLoopbackOption,
                              options.testFlag(HbTcpConfig::SocketOption::MulticastLoopback));

    return mpSocket;
}

HbAbstractSocket* HbTcpClient::currentConnection() const {
    return mpSocket;
}
