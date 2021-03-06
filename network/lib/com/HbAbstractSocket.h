#ifndef HBABSTRACTSOCKET_H
#define HBABSTRACTSOCKET_H

/*! \file HbAbstractSocket.h */

// Qt
#include <QtCore/QDataStream>
#include <QtCore/QPointer>
#include <QtCore/QQueue>
#include <QtNetwork/QAbstractSocket>
// Hb
#include <HbGlobal.h>
#include <contract/HbNetworkContract.h>
#include <contract/HbNetworkProtocol.h>
#include <core/HbUid.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HbAbstractSocket : public QObject,
                         public HbUid<CLASS_SOCKET> // 0 is excluded, HbNetworkContract::sender() returns 0 when the
                                                    // server is the sender.
{
    Q_OBJECT
    Q_DISABLE_COPY(HbAbstractSocket)

public:
    virtual ~HbAbstractSocket();

    virtual HbNetworkProtocol::NetworkType type() const = 0;
    virtual bool isListening() const = 0;
    virtual bool leave() = 0;

    virtual QAbstractSocket::SocketError error() const = 0;
    virtual QAbstractSocket::SocketState state() const = 0;
    virtual QString errorString() const;

    bool sendContract(ShConstHbNetworkContract contract);
    virtual QByteArray readPacket();
    virtual qint64 writePacket(const QByteArray& packet) const;
    virtual bool packetAvailable() const;

signals:
    void socketReadyPacket();
    void socketStateChanged(); // Used in children.
    void socketError();        // Used in children.
    void socketConnected();    // Used in childen.
    void socketDisconnected(); // Used in children.

protected:
    HbAbstractSocket() = delete;
    HbAbstractSocket(QIODevice* device, QObject* parent = nullptr);

    virtual qint64 readStream(QDataStream& stream);
    virtual qint64 writeBuffer(const QByteArray& buffer) const;

    // From children device.
    virtual void onReadyRead() = 0;

private:
    QPointer<QIODevice> mDevice;

    quint32 mBytesPending;
    QQueue<QByteArray> mPackets;
};
} // namespace network
} // namespace hb

#endif // HBABSTRACTSOCKET_H
