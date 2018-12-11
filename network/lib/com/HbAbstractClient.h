/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBABSTRACTCLIENT_H
#define HBABSTRACTCLIENT_H

/*! \file HbAbstractClient.h */

// Hb
#include <HbGlobal.h>
// Local
#include <HbNetwork.h>
#include <com/HbAbstractNetwork.h>
#include <config/com/HbClientConfig.h>

namespace hb {
namespace network {

class HbAbstractSocket;

/*!
 * TODOC
 */
class HB_NETWORK_DECL HbAbstractClient : public HbAbstractNetwork {
    Q_OBJECT
    Q_DISABLE_COPY(HbAbstractClient)

public:
    virtual ~HbAbstractClient() = default;

    virtual bool join();
    virtual bool leave();
    virtual bool isReady() const;
    virtual networkuid uid() const = 0;

    virtual bool send(ShConstHbNetworkContract contract);

    virtual const HbClientConfig& configuration() const; // SUB

signals:
    void clientConnected(networkuid client_uid);
    void clientDisconnected(networkuid client_uid);
    void clientContractReceived(networkuid client_uid, const HbNetworkContract* contract);

protected:
    HbAbstractClient(QObject* parent = nullptr);

    virtual void deleteSocket() = 0;

    virtual HbAbstractSocket* pendingConnection() = 0;
    virtual HbAbstractSocket* currentConnection() const = 0;

private:
    void timerEvent(QTimerEvent* event);

private
    callbacks : // From device.
                void
                onSocketConnected();
    void onSocketReadyPacket();
    void onSocketDisconnected();

private:
    HbClientConfig mConfig; // SUB
    qint32 mRetry;
    bool mReady;
};

} // namespace network
} // namespace hb

#endif // HBABSTRACTCLIENT_H
