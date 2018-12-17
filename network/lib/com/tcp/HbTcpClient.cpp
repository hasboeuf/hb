// Qt
#include <QtNetwork/QTcpSocket>
// Hb
#include <HbLogService.h>
// Local
#include <com/tcp/HbTcpClient.h>
#include <com/tcp/HbTcpSocket.h>

using namespace hb::network;

HbTcpClient::HbTcpClient(QObject* parent) : HbAbstractClient(parent) {
    mSocket = nullptr;
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
    if (mSocket) {
        return mSocket->uid();
    } else {
        return 0;
    }
}

HbNetworkProtocol::NetworkType HbTcpClient::type() const {
    if (mSocket) {
        return mSocket->type();
    } else {
        return HbNetworkProtocol::NETWORK_UNDEFINED;
    }
}

bool HbTcpClient::setConfiguration(const HbTcpClientConfig& config) {
    if (mSocket) {
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
    Q_ASSERT(mSocket);
    if (!mSocket->connectToHost(this->configuration())) {
        qWarning() << "Can not connect to host";
        return false;
    }

    return true;
}

void HbTcpClient::disconnectFromNetwork() {
    Q_ASSERT(mSocket);
    if (!mSocket->leave()) {
        qWarning() << "Can not disconnect from host";
    } else {
        deleteSocket();
    }
}

void HbTcpClient::deleteSocket() {
    mSocket->disconnect();
    mSocket->deleteLater();
    mSocket = nullptr;
}

HbAbstractSocket* HbTcpClient::pendingConnection() {
    if (mSocket) {
        return mSocket;
    }

    QTcpSocket* device = q_check_ptr(new QTcpSocket(this));
    mSocket = q_check_ptr(new HbTcpSocket(device));

    connect(mSocket,
            &HbAbstractSocket::socketError,
            this,
            [this]() { emit socketError(mSocket->error(), mSocket->errorString()); },
            Qt::UniqueConnection);

    HbTcpConfig::SocketOptions options = mConfig.options();

    mSocket->setSocketOption(QAbstractSocket::LowDelayOption, options.testFlag(HbTcpConfig::SocketOption::LowDelay));
    mSocket->setSocketOption(QAbstractSocket::KeepAliveOption, options.testFlag(HbTcpConfig::SocketOption::KeepAlive));
    mSocket->setSocketOption(QAbstractSocket::MulticastLoopbackOption,
                             options.testFlag(HbTcpConfig::SocketOption::MulticastLoopback));

    return mSocket;
}

HbAbstractSocket* HbTcpClient::currentConnection() const {
    return mSocket;
}
