/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSOCKETHANDLER_H
#define HBSOCKETHANDLER_H

/*! \file HbSocketHandler.h */

// Qt
#include <QtCore/QMap>
#include <QtCore/QMutex>
#include <QtCore/QObject>
// Hb
#include <HbGlobal.h>
#include <contract/HbNetworkContract.h>
// Local
#include <com/HbAbstractServer.h> // Covariance.

namespace hb {
namespace network {
class HbAbstractSocket;

/*!
 * TODOC
 */
class HbSocketHandler : public QObject, public HbUid<CLASS_SERVER> {
    Q_OBJECT
    Q_DISABLE_COPY(HbSocketHandler)
    friend class HbAbstractServer;

public:
    virtual bool canHandleNewConnection();

protected:
    enum HandlerState { NOT_THREADED = 0, THREADED };

    HbSocketHandler();
    virtual ~HbSocketHandler();

    virtual HbAbstractServer* server() const = 0;

    virtual bool storeNewSocket(HbAbstractSocket* socket, qint32 previous_uid);

protected:
    virtual void reset();

protected:
    HandlerState mState;

    QHash<networkuid, HbAbstractSocket*> mSocketById;
    QHash<HbAbstractSocket*, networkuid> mIdBySocket;

    QMutex mSocketMutex;

public slots:
    // From QThread
    virtual void init();
    // From Server
    virtual void onNewPendingConnection(qint32 socket_descriptor) = 0;
    virtual void onDisconnectionRequest(networkuid uid);
    virtual void onServerLeft();
    virtual void onSendContract(ShConstHbNetworkContract contract); // Send to all.
    virtual void onSendContract(networkuid socket_uid, ShConstHbNetworkContract contract);
    // From Socket
    virtual void onSocketReadyPacket();
    virtual void onSocketDisconnected();

signals:
    // To Server.
    void handlerIdled();
    void socketConnected(qint32 socket_previous_id, networkuid socket_id);
    void socketDisconnected(networkuid socket_uid);
    void socketContractReceived(networkuid socket_uid, const HbNetworkContract* contract);
};
} // namespace network
} // namespace hb

#endif // HBSOCKETHANDLER_H
