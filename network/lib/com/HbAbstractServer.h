#ifndef HBABSTRACTSERVER_H
#define HBABSTRACTSERVER_H

/*! \file HbAbstractServer.h */

// Qt
#include <QtCore/QHash>
#include <QtCore/QList>
#include <QtCore/QSharedPointer>
// Hb
#include <core/HbUid.h>
// Local
#include <com/HbAbstractNetwork.h>
#include <config/com/HbServerConfig.h>

namespace hb {
namespace network {

class HbSocketHandler;

/*!
 * TODOC
 */
class HB_NETWORK_DECL HbAbstractServer : public HbAbstractNetwork, public HbUid<CLASS_SERVER> {
    Q_OBJECT
    Q_DISABLE_COPY(HbAbstractServer)
    friend class HbSocketHandler;

public:
    virtual ~HbAbstractServer() =
        default; // Keep it, inherited classes should handle deletion to avoid pure virtual calls.

    virtual bool join();
    virtual bool leave();
    virtual bool leave(networkuid uid);
    virtual bool isReady() const;

    virtual bool send(ShConstHbNetworkContract contract);

    virtual bool isUidConnected(networkuid uid) const;

    virtual const HbServerConfig& configuration() const; // SUB

    // From HbSocketHandler.
    void onSocketConnected(qint32 socket_descriptor, networkuid socket_uid);
    void onSocketDisconnected(networkuid socket_uid);
    void onSocketContractReceived(networkuid socket_uid, const HbNetworkContract* contract);
    void onHandlerIdled();

signals:
    void serverConnected(networkuid server_uid);
    void serverDisconnected(networkuid server_uid);
    // To higher level class.
    void socketConnected(networkuid server_uid, networkuid socket_uid);
    void socketDisconnected(networkuid server_uid, networkuid socket_uid);
    void socketContractReceived(networkuid server_uid, networkuid socket_uid, const HbNetworkContract* contract);

protected:
    HbAbstractServer(QObject* parent = nullptr);

    virtual bool isListening() const = 0; // From device.

    virtual void reset();

    QList<qint32> mPending; // Socket descriptors not instanciated.
    QHash<networkuid, HbSocketHandler*> mHandlerBySocketId;
    QHash<networkuid, HbSocketHandler*> mHandlerById;

private:
    HbServerConfig mConfig; // SUB
    bool mReady;
};
} // namespace network
} // namespace hb

#endif // HBABSTRACTSERVER_H
