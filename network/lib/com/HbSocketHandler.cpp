// Qt
#include <QtCore/QMutexLocker>
#include <QtCore/QTimer>
#include <QtNetwork/QTcpSocket>
// Hb
#include <HbGlobal.h>
#include <HbLogService.h>
// Local
#include <com/HbAbstractServer.h>
#include <com/HbAbstractSocket.h>
#include <com/HbSocketHandler.h>
#include <config/com/HbNetworkConfig.h>
#include <contract/HbNetworkHeader.h>

using namespace hb::tools;
using namespace hb::log;
using namespace hb::network;

HbSocketHandler::HbSocketHandler() : QObject(nullptr) {
    mState = NOT_THREADED;
}

HbSocketHandler::~HbSocketHandler() {
    reset();
}

void HbSocketHandler::init() {
    mState = THREADED;
}

void HbSocketHandler::reset() {
    qDebug() << "Reset socket handler" << mUid;
    QMutexLocker locker(&mSocketMutex);

    for (HbAbstractSocket* socket : mSocketById.values()) {
        qDebug() << "Delete socket" << socket->uid();
        delete socket;
    }

    mSocketById.clear();
    mIdBySocket.clear();
}

bool HbSocketHandler::canHandleNewConnection() {
    QMutexLocker locker(&mSocketMutex);

    bool is_threaded = server()->configuration().isThreaded();
    if (!is_threaded
        || (is_threaded && mState == THREADED && mSocketById.size() < server()->configuration().maxUsersPerThread())) {
        return true;
    }

    qWarning() << QString("SocketHandler %1: Cannot handle new socket. [state=%2, size=%3, max=%4].")
                      .arg(mUid)
                      .arg(mState)
                      .arg(mSocketById.size())
                      .arg(server()->configuration().maxUsersPerThread());
    return false;
}

bool HbSocketHandler::storeNewSocket(HbAbstractSocket* socket, qint32 previous_uid) {
    QMutexLocker locker(&mSocketMutex);

    // q_assert( socket->type() != HbAbstractSocket::UdpSocket );

    q_assert_ptr(socket);

    mSocketById.insert(socket->uid(), socket);
    mIdBySocket.insert(socket, socket->uid());

    connect(socket,
            &HbAbstractSocket::socketReadyPacket,
            this,
            &HbSocketHandler::onSocketReadyPacket,
            Qt::UniqueConnection);
    connect(socket,
            &HbAbstractSocket::socketDisconnected,
            this,
            &HbSocketHandler::onSocketDisconnected,
            Qt::UniqueConnection);
    connect(socket,
            &HbAbstractSocket::socketError,
            this,
            [this, socket]() {
                qWarning() << QString("Error %1 (%2) on socket %3")
                                  .arg(socket->error())
                                  .arg(socket->errorString())
                                  .arg(socket->uid());
            },
            Qt::UniqueConnection);

    qDebug()
        << QString("Handler %1: socket %2 (descriptor=%3) instanciated").arg(mUid).arg(socket->uid()).arg(previous_uid);

    emit socketConnected(previous_uid, socket->uid()); // To Server.

    return true;
}

void HbSocketHandler::onDisconnectionRequest(networkuid uid) {
    HbAbstractSocket* socket = nullptr;

    { // Scoped mutex to avoid deadlock with onSocketDisconnected slot.
        QMutexLocker locker(&mSocketMutex);
        socket = mSocketById.value(uid, nullptr);
    }

    if (socket) {
        socket->leave();
        // onSocketDisconnected handles the rest.
    } else {
        qWarning() << QString("Socket %1 does not exist for hander %2").arg(uid).arg(mUid);
    }
}

void HbSocketHandler::onServerLeft() {
    qDebug() << "Server left -> deleting this handler" << mUid;
    reset();
}

void HbSocketHandler::onSendContract(ShConstHbNetworkContract contract) {
    for (networkuid socket_uid : mSocketById.keys()) {
        onSendContract(socket_uid, contract);
    }
}

void HbSocketHandler::onSendContract(networkuid socket_uid, ShConstHbNetworkContract contract) {
    HbAbstractSocket* socket = mSocketById.value(socket_uid, nullptr);
    if (!socket) {
        qWarning() << "Socket" << socket_uid << "does not exist in this handler";
        return;
    }

    if (!socket->isListening()) {
        qWarning() << "Unable to send contract on inactive socket";
        return;
    }

    if (!socket->sendContract(contract)) {
        qWarning() << QString("Error writing contract %1 in socket %2").arg(contract->uid()).arg(socket_uid);
        //! \todo Use socket error string.
    }
}

void HbSocketHandler::onSocketReadyPacket() {
    HbAbstractSocket* socket = q_assert_ptr(dynamic_cast<HbAbstractSocket*>(sender()));

    bool available = (socket->isListening() && socket->packetAvailable());

    while (available) {
        QByteArray packet = socket->readPacket();

        if (!server()->configuration().openMode().testFlag(QIODevice::ReadOnly)) {
            qWarning() << "Unable to receive contract on write only socket" << socket->uid();
        } else {
            QDataStream stream(&packet, QIODevice::ReadOnly);

            HbNetworkHeader header;
            stream >> header;
            q_assert(stream.status() == QDataStream::Ok);

            if (!server()->configuration().isBadHeaderTolerant()) {
                if (!HbAbstractNetwork::checkHeader(header)) {
                    qWarning() << QString("Bad contract header (app=%1, protocol=%2. Kick")
                                      .arg(header.appName())
                                      .arg(header.protocolVersion());
                    socket->leave();
                    return;
                }
            }

            HbNetworkContract* contract = server()->configuration().exchanges().contract(header);

            if (!contract) {
                qWarning() << "Try to read unregistered contract" << contract->header().toString();
            } else {
                if (!contract->read(stream)) {
                    q_assert(stream.status() == QDataStream::Ok);

                    qWarning() << "Error occurred while reading contract" << contract->header().toString();
                } else {
                    contract->setSender(socket->uid());
                    contract->setNetworkType(server()->type());
                    contract->updateReply(); // In case of a reply-able contract.

                    emit socketContractReceived(socket->uid(), contract);
                }
            }
        }

        available = (socket->isListening() && socket->packetAvailable());
    }
}

void HbSocketHandler::onSocketDisconnected() {
    QMutexLocker locker(&mSocketMutex);

    HbAbstractSocket* socket = q_assert_ptr(dynamic_cast<HbAbstractSocket*>(sender()));

    q_assert(mIdBySocket.contains(socket));
    q_assert(mSocketById.contains(socket->uid()));

    qDebug() << QString("SocketPool %1: Socket %2 disconnected.").arg(mUid).arg(socket->uid());

    networkuid uid = socket->uid();

    mIdBySocket.remove(socket);
    mSocketById.remove(uid);

    socket->disconnect();
    socket->deleteLater();

    emit socketDisconnected(uid);

    if (mSocketById.isEmpty()) {
        emit handlerIdled();
    }
}
