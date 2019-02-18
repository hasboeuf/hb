#ifndef HBCLIENT_H
#define HBCLIENT_H

/*! \file HbClient.h */

// Qt
// Hb
#include <HbLogService.h>
// Local
#include <HbClientConnectionPool.h>
#include <HbNetwork.h>
#include <HbPeer.h>
#include <config/peer/HbGeneralClientConfig.h>
#include <service/auth/HbAuthService.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbClient : public HbPeer {
    Q_OBJECT
    Q_DISABLE_COPY(HbClient)
public:
    HbClient() = delete;
    HbClient(const HbGeneralClientConfig& config);
    virtual ~HbClient() = default;

    networkuid joinTcpClient(HbTcpClientConfig& config, bool main);
    virtual bool leave() override;

    bool authRequest(HbClientAuthLoginObject* login_object);
    bool OAuthRequested(HbAuthService::AuthType type);

signals:
    void clientStatusChanged(networkuid client_uid, HbNetworkProtocol::ClientStatus status);
    void meStatusChanged(HbNetworkProtocol::UserStatus me_status, ShConstHbNetworkUserInfo me_info);

private:
    HbClientConnectionPool mConnectionPool;
};
} // namespace network
} // namespace hb

#endif // HBCLIENT_H
