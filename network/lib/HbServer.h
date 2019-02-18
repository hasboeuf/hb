#ifndef HBSERVER_H
#define HBSERVER_H

/*! \file HbServer.h */

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <HbPeer.h>
#include <HbServerConnectionPool.h>
#include <config/peer/HbGeneralServerConfig.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbServer : public HbPeer {
    Q_OBJECT
    Q_DISABLE_COPY(HbServer)
public:
    HbServer() = delete;
    HbServer(const HbGeneralServerConfig& config);
    virtual ~HbServer();

    networkuid joinTcpServer(HbTcpServerConfig& config, bool main);
    virtual bool leave() override;

signals:
    void serverStatusChanged(networkuid server_uid, HbNetworkProtocol::ServerStatus status);

private:
    HbServerConnectionPool mConnectionPool;
};
} // namespace network
} // namespace hb

#endif // HBSERVER_H
