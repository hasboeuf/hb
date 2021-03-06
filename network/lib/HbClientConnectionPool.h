#ifndef HBCLIENTCONNECTIONPOOL_H
#define HBCLIENTCONNECTIONPOOL_H

/*! \file HbClientConnectionPool.h */

// Qt
#include <QtCore/QHash>
// Hb
// Local
#include <HbConnectionPool.h>
#include <HbNetwork.h>
#include <config/com/HbTcpClientConfig.h>
#include <config/peer/HbGeneralClientConfig.h>
#include <user/HbClientUser.h>

namespace hb {
namespace network {
class HbAbstractClient;
class HbClientAuthLoginObject;

/*!
 * TODOC
 */
class HB_NETWORK_DECL HbClientConnectionPool : public HbConnectionPool {
    Q_OBJECT
public:
    HbClientConnectionPool() = delete;
    HbClientConnectionPool(const HbGeneralClientConfig& config);
    virtual ~HbClientConnectionPool();

    networkuid joinTcpClient(HbTcpClientConfig& config, bool main);
    virtual bool leave() override;

    bool authRequested(HbClientAuthLoginObject* login_object);

    // From HbAbstractClient.
    void onClientConnected(networkuid client_uid);
    void onClientDisconnected(networkuid client_uid);
    void onClientContractReceived(networkuid client_uid, const HbNetworkContract* contract);

    // From services.
    void onContractToSend(const HbNetworkContract* contract) override;

    // From HbAuthService.
    void onSocketAuthenticated(networkuid socket_uid, const HbNetworkUserInfo& user_info) override;
    void
    onSocketUnauthenticated(networkuid socket_uid, quint8 try_number, quint8 max_tries, const QString& reason) override;

    // From HbNetworkUser.
    void onMeStatusChanged(HbNetworkProtocol::UserStatus me_status);

signals:
    void statusChanged(networkuid client_uid, HbNetworkProtocol::ClientStatus status);
    void meStatusChanged(HbNetworkProtocol::UserStatus status_me, ShConstHbNetworkUserInfo me_info);

private:
    bool checkKickReceived(const HbNetworkContract* contract);

    QHash<networkuid, HbAbstractClient*> mClients;
    HbClientUser mUser;
};
} // namespace network
} // namespace hb

#endif // HBCLIENTCONNECTIONPOOL_H
