// Qt
#include <QtNetwork/QTcpSocket>
// Hb
#include <HbLogService.h>
// Local
#include <com/tcp/HbTcpSocket.h>

using namespace hb::network;

HbTcpSocket::HbTcpSocket(QTcpSocket* device) : HbAbstractSocket(device) {
    Q_ASSERT(device);
    mDevice = device;

    connect(mDevice, &QTcpSocket::stateChanged, this, &HbTcpSocket::onStateChanged, Qt::UniqueConnection);
    connect(mDevice, (void (QTcpSocket::*)(QAbstractSocket::SocketError)) & QTcpSocket::error, [this]() {
        emit socketError();
    });
}

HbTcpSocket::~HbTcpSocket() {
    // HbAbstractSocket handles the destruction.
}

HbNetworkProtocol::NetworkType HbTcpSocket::type() const {
    return HbNetworkProtocol::NETWORK_TCP;
}

bool HbTcpSocket::connectToHost(const HbTcpConfig& config) {
    if (state() == QAbstractSocket::UnconnectedState) {
        mConfig = config;
        mDevice->connectToHost(mConfig.address(), mConfig.port(), QIODevice::ReadWrite);

        return true;
    }

    return false;
}

bool HbTcpSocket::leave() {
    if (state() != QAbstractSocket::UnconnectedState) {
        mDevice->disconnectFromHost();
        return true;
    }

    return false;
}

bool HbTcpSocket::isListening() const {
    return (state() == QAbstractSocket::ConnectedState);
}

void HbTcpSocket::setSocketOption(QAbstractSocket::SocketOption option, bool enable) {
    switch (option) {
    case QAbstractSocket::LowDelayOption:
    case QAbstractSocket::KeepAliveOption:
    case QAbstractSocket::MulticastLoopbackOption:

        mDevice->setSocketOption(option, enable);
        break;

    default:

        Q_UNREACHABLE();
        break;
    }
}

bool HbTcpSocket::socketOption(QAbstractSocket::SocketOption option) const {
    switch (option) {
    case QAbstractSocket::LowDelayOption:
    case QAbstractSocket::KeepAliveOption:
    case QAbstractSocket::MulticastLoopbackOption:
        return mDevice->socketOption(option).toBool();

    default:
        return false;
    }
}

QAbstractSocket::SocketError HbTcpSocket::error() const {
    return mDevice->error();
}

QAbstractSocket::SocketState HbTcpSocket::state() const {
    return mDevice->state();
}

void HbTcpSocket::onReadyRead() {
    QDataStream stream(mDevice);

    if (readStream(stream) < 0) {
        qWarning() << "Read stream failed";
    }
}

void HbTcpSocket::onStateChanged(QAbstractSocket::SocketState state) {
    Q_ASSERT(mDevice == sender());

    if (state == QAbstractSocket::UnconnectedState) {
        qDebug() << "Socket enters UnconnectedState";
        emit socketDisconnected();
    } else if (state == QAbstractSocket::HostLookupState) {
        qDebug() << "Socket enters HostLookupState";
    } else if (state == QAbstractSocket::ConnectingState) {
        qDebug() << "Socket enters ConnectingState";
    } else if (state == QAbstractSocket::ConnectedState) {
        qDebug() << "Socket enters ConnectedState";
        emit socketConnected();
    } else if (state == QAbstractSocket::BoundState) {
        qDebug() << "Socket enters BoundState";
    } else if (state == QAbstractSocket::ClosingState) {
        qDebug() << "Socket enters ClosingState";
    } else if (state == QAbstractSocket::ListeningState) {
        qDebug() << "Socket enters ListeningState";
    }

    emit socketStateChanged();
}
