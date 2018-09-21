// Qt
#include <QtCore/QSharedPointer>
// Hb
#include <HbLogService.h>
// Local
#include <com/HbAbstractServer.h>
#include <com/HbAbstractSocket.h>
#include <com/HbSocketHandler.h>
#include <config/com/HbNetworkConfig.h>
#include <contract/HbNetworkHeader.h>

using namespace hb::tools;
using namespace hb::network;

HbAbstractServer::HbAbstractServer(QObject* parent) : HbAbstractNetwork(parent) {
    mReady = false;
}

bool HbAbstractServer::join() {
    if (!isListening()) {
        if (!configuration().isValid()) {
            qWarning() << "Invalid server configuration";
            return false;
        }

        if (connectToNetwork()) {
            mReady = true;
            emit serverConnected(mUid);
        }
    }

    return isListening();
}

bool HbAbstractServer::leave() {
    if (isListening()) {
        disconnectFromNetwork();
        mReady = false;
        reset();
        emit serverDisconnected(mUid);

        qDebug() << "Server stopped";
    } else {
        qDebug() << "Server already stopped";
    }

    return true;
}

bool HbAbstractServer::leave(networkuid uid) {
    qDebug() << "Disconnecting socket" << uid;
    HbSocketHandler* handler = mHandlerBySocketId.value(uid, nullptr);
    q_assert_ptr(handler);

    q_assert(QMetaObject::invokeMethod(handler, "onDisconnectionRequest", Q_ARG(networkuid, uid)));
    return true;
}

bool HbAbstractServer::isReady() const {
    return mReady;
}

bool HbAbstractServer::send(ShConstHbNetworkContract contract) {
    if (contract.isNull()) {
        qWarning() << "Try to send a null contract";
    } else {
        if (!isListening()) {
            qWarning() << "Unable to send contract on inactive server";
        } else {
            if (!configuration().exchanges().registered(contract->header().service(), contract->header().code())) {
                qWarning() << "Try to send an unregistered contract" << contract->header().toString();

                return false;
            }

            if (contract->routing() == HbNetworkProtocol::ROUTING_UNICAST) {
                networkuid receiver = contract->receiver();
                if (receiver != 0) {
                    HbSocketHandler* handler = mHandlerBySocketId.value(receiver, nullptr);
                    if (!handler) {
                        qWarning() << "Unable to send contract, socket" << receiver << "does not exist";
                    } else {
                        q_assert(QMetaObject::invokeMethod(handler,
                                                           "onSendContract",
                                                           Q_ARG(networkuid, receiver),
                                                           Q_ARG(ShConstHbNetworkContract, contract)));
                    }
                } else {
                    qWarning() << "Try to send an incompatible UNICAST contract";
                }
            } else if (contract->routing() == HbNetworkProtocol::ROUTING_MULTICAST) {
                // Retrieve socket handler.
                for (networkuid receiver : contract->receivers()) {
                    HbSocketHandler* handler = mHandlerBySocketId.value(receiver, nullptr);
                    if (!handler) {
                        qWarning() << "Unable to send contract, socket" << receiver << "does not exist";
                    } else {
                        q_assert(QMetaObject::invokeMethod(handler,
                                                           "onSendContract",
                                                           Q_ARG(networkuid, receiver),
                                                           Q_ARG(ShConstHbNetworkContract, contract)));
                    }
                }
            } else // HbNetworkProtocol::BROADCAST
            {
                for (HbSocketHandler* handler : mHandlerById.values()) {
                    q_assert_ptr(handler);
                    q_assert(QMetaObject::invokeMethod(
                        handler, "onSendContract", Q_ARG(ShConstHbNetworkContract, contract)));
                }
            }
        }
    }

    return false;
}

bool HbAbstractServer::isUidConnected(networkuid uid) const {
    return mHandlerBySocketId.contains(uid);
}

const HbServerConfig& HbAbstractServer::configuration() const // SUB
{
    return mConfig;
}

void HbAbstractServer::reset() {
    qDebug() << "Reset server...";

    mPending.clear();
    for (HbSocketHandler* handler : mHandlerById.values()) {
        q_assert_ptr(handler);
        qDebug() << "Deleting handler" << handler->uid();
        handler->disconnect();
        handler->deleteLater();
    }
    mPending.clear();
    mHandlerById.clear();
    mHandlerBySocketId.clear();
}

void HbAbstractServer::onSocketConnected(qint32 socket_descriptor, networkuid socket_uid) {
    if (!mReady) {
        qDebug() << "Server not ready, no treatments for onSocketConnected()";
        return;
    }

    HbSocketHandler* handler = qobject_cast<HbSocketHandler*>(sender());
    q_assert_ptr(handler);
    q_assert(mPending.contains(socket_descriptor));
    q_assert(!mHandlerBySocketId.contains(socket_uid));

    qDebug() << QString("New socket %1 connected (descriptor=%2) on handler %3")
                    .arg(socket_uid)
                    .arg(socket_descriptor)
                    .arg(handler->uid());

    mPending.removeOne(socket_descriptor);
    mHandlerBySocketId.insert(socket_uid, handler);

    emit socketConnected(mUid, socket_uid);
}

void HbAbstractServer::onSocketDisconnected(networkuid socket_uid) {
    if (!mReady) {
        qDebug() << "Server not ready, no treatments for onSocketDisconnected()";
        return;
    }
    HbSocketHandler* handler = qobject_cast<HbSocketHandler*>(sender());
    q_assert_ptr(handler);
    q_assert(mHandlerBySocketId.value(socket_uid) == handler);

    mHandlerBySocketId.remove(socket_uid);

    emit socketDisconnected(mUid, socket_uid);
}

void HbAbstractServer::onSocketContractReceived(networkuid socket_uid, const HbNetworkContract* contract) {
    if (!mReady) {
        qDebug() << "Server not ready, no treatments for onSocketContractReceived()";
        delete contract;
        return;
    }
    emit socketContractReceived(mUid, socket_uid, contract);
}

void HbAbstractServer::onHandlerIdled() {
    if (!mReady) {
        qDebug() << "Server not ready, no treatments for onHandlerIdled()";
        return;
    }
    HbSocketHandler* handler = qobject_cast<HbSocketHandler*>(sender());
    q_assert_ptr(handler);

    mHandlerById.remove(handler->uid());

    handler->disconnect();
    handler->deleteLater();
}
