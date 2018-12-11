// Qt
#include <QtCore/QThread>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
// Hb
#include <HbLogService.h>
// Local
#include <com/tcp/HbTcpServer.h>
#include <com/tcp/HbTcpSocket.h>
#include <com/tcp/HbTcpSocketHandler.h>

using namespace hb::network;

TcpServer::TcpServer(QObject* parent) : QTcpServer(parent) {
}

void TcpServer::incomingConnection(qintptr socket_descriptor) {
    //! \todo Switch to qintptr for internal structure.
    emit newConnection(socket_descriptor);
}

HbTcpServer::HbTcpServer(QObject* parent) : HbAbstractServer(parent) {
    mpDevice = q_check_ptr(new TcpServer(this));

    connect(mpDevice, &TcpServer::newConnection, this, &HbTcpServer::onNewConnection, Qt::UniqueConnection);
}

HbTcpServer::~HbTcpServer() {
    leave();
}

bool HbTcpServer::join(const HbTcpServerConfig& config) {
    if (!setConfiguration(config)) {
        return false;
    }

    return HbAbstractServer::join();
}

bool HbTcpServer::setConfiguration(const HbTcpServerConfig& config) {
    if (isListening()) {
        qWarning() << "Can not set configuration, server is listening";
        return false;
    }

    reset();

    mConfig = config;

    return true;
}

const HbTcpServerConfig& HbTcpServer::configuration() const {
    return mConfig;
}

void HbTcpServer::reset() {
    HbAbstractServer::reset();
}

bool HbTcpServer::connectToNetwork() {
    quint16 port = configuration().port();

    if (!mpDevice->listen(configuration().address(), port)) {
        qWarning() << "Server failed to listen";
        return false;
    }

    qDebug() << "Server started on port" << port;
    return true;
}

void HbTcpServer::disconnectFromNetwork() {
    mpDevice->close();
}

bool HbTcpServer::isListening() const {
    return mpDevice->isListening();
}

HbNetworkProtocol::NetworkType HbTcpServer::type() const {
    return HbNetworkProtocol::NETWORK_TCP;
}

void HbTcpServer::onNewConnection(qint32 socket_descriptor) {
    if (!isReady()) {
        qDebug() << "Server not ready, no treatments for onNewConnection()";
        return;
    }

    HbSocketHandler* handler = nullptr;

    // Seeking an available handler.
    for (HbSocketHandler* h : mHandlerById.values()) {
        if (h->canHandleNewConnection()) {
            handler = h;
        }
    }

    // We must create one.
    if (!handler) {
        handler = new HbTcpSocketHandler(this);

        bool is_threaded = mConfig.maxUsersPerThread() > 0;
        // Must be threaded.
        if (is_threaded) {
            QThread* t = new QThread();
            handler->moveToThread(t);

            //! \todo Redesign this part?
            connect(t, &QThread::started, handler, &HbSocketHandler::init, Qt::UniqueConnection);
            connect(handler, &QObject::destroyed, t, &QThread::quit, Qt::UniqueConnection);
            connect(t, &QThread::finished, t, &QThread::deleteLater, Qt::UniqueConnection);

            t->start();
        }

        connect(handler,
                &HbSocketHandler::socketConnected,
                this,
                &HbAbstractServer::onSocketConnected,
                Qt::UniqueConnection);
        connect(handler,
                &HbSocketHandler::socketDisconnected,
                this,
                &HbAbstractServer::onSocketDisconnected,
                Qt::UniqueConnection);
        connect(handler,
                &HbSocketHandler::socketContractReceived,
                this,
                &HbAbstractServer::onSocketContractReceived,
                Qt::UniqueConnection);
        connect(handler, &HbSocketHandler::handlerIdled, this, &HbAbstractServer::onHandlerIdled, Qt::UniqueConnection);

        mHandlerById.insert(handler->uid(), handler);

        qDebug() << "Handler" << handler->uid() << "created to handle socket" << socket_descriptor;
    }

    mPending.append(socket_descriptor);
    bool ok = QMetaObject::invokeMethod(handler, "onNewPendingConnection", Q_ARG(qint32, socket_descriptor));
    Q_ASSERT(ok);
}
