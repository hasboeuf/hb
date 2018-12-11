#ifndef HBTCPSERVER_H
#define HBTCPSERVER_H

/*! \file HbTcpServer.h */

// Qt
#include <QtNetwork/QTcpServer>
// Local
#include <com/HbAbstractServer.h>
#include <config/com/HbTcpServerConfig.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class TcpServer : public QTcpServer {
    Q_OBJECT
    Q_DISABLE_COPY(TcpServer)
    friend class HbTcpServer;

signals:
    void newConnection(qint32 socket_descriptor);

protected:
    TcpServer(QObject* parent = nullptr);
    void incomingConnection(qintptr socket_descriptor) override;
};

class HB_NETWORK_DECL HbTcpServer : public HbAbstractServer {
    Q_OBJECT
    Q_DISABLE_COPY(HbTcpServer)

public:
    HbTcpServer(QObject* parent = nullptr);
    virtual ~HbTcpServer();

    using HbAbstractServer::join;
    virtual bool join(const HbTcpServerConfig& config);

    virtual bool setConfiguration(const HbTcpServerConfig& config);
    virtual const HbTcpServerConfig& configuration() const;

signals:
    // To HbTcpSocketHandler.
    void newConnection(qint32 socket_descriptor);

private:
    virtual bool connectToNetwork() override;
    virtual void disconnectFromNetwork() override;
    virtual bool isListening() const override;
    virtual HbNetworkProtocol::NetworkType type() const override;

    virtual void reset();

    // From device.
    void onNewConnection(qint32 socket_descriptor);

    TcpServer* mpDevice;
    HbTcpServerConfig mConfig;
};
} // namespace network
} // namespace hb

using hb::network::HbTcpServer;

#endif // HBTCPSERVER_H
