// Qt
#include <QtCore/QTimer>
#include <QtNetwork/QTcpSocket>
// Hb
#include <HbGlobal.h>
#include <HbLogService.h>
// Local
#include <com/tcp/HbTcpServer.h>
#include <com/tcp/HbTcpSocket.h>
#include <com/tcp/HbTcpSocketHandler.h>

using namespace hb::tools;
using namespace hb::log;
using namespace hb::network;

HbTcpSocketHandler::HbTcpSocketHandler(HbTcpServer* server) : HbSocketHandler() {
    Q_ASSERT(server);
    mServer = server;
}

HbTcpSocketHandler::~HbTcpSocketHandler() {
    reset();
}

HbTcpServer* HbTcpSocketHandler::server() const {
    return mServer;
}

void HbTcpSocketHandler::init() {
    HbSocketHandler::init();
}

void HbTcpSocketHandler::reset() {
}

void HbTcpSocketHandler::onNewPendingConnection(qint32 socket_descriptor) {
    if (!canHandleNewConnection()) {
        qWarning() << QString("Handler %1: cannot handle socket descriptor %2").arg(mUid).arg(socket_descriptor);
        // Creating a volatile socket to disconnect the descriptor.
        QTcpSocket* socket = new QTcpSocket();
        socket->setSocketDescriptor(socket_descriptor);
        socket->close();
        delete socket;
        return;
    }

    QTcpSocket* device = new QTcpSocket();
    bool ok = device->setSocketDescriptor(socket_descriptor);
    Q_ASSERT(ok);

    HbTcpSocket* socket = new HbTcpSocket(device);

    HbTcpConfig::SocketOptions options = mServer->configuration().options();
    socket->setSocketOption(QAbstractSocket::LowDelayOption, options.testFlag(HbTcpConfig::SocketOption::LowDelay));
    socket->setSocketOption(QAbstractSocket::KeepAliveOption, options.testFlag(HbTcpConfig::SocketOption::KeepAlive));
    socket->setSocketOption(QAbstractSocket::MulticastLoopbackOption,
                            options.testFlag(HbTcpConfig::SocketOption::MulticastLoopback));

    storeNewSocket(socket, socket_descriptor);
}
