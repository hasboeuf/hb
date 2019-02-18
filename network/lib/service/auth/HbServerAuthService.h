#ifndef HBSERVERAUTHSERVICE_H
#define HBSERVERAUTHSERVICE_H

/*! \file HbServerAuthService.h */

// Qt
// Hb
// Local
#include <config/service/auth/HbServiceAuthServerConfig.h>
#include <service/auth/HbAuthService.h>

class QTimerEvent;

namespace hb {
namespace network {

class HbServerAuthStrategy;
class HbAuthStatusContract;

/*!
 * TODOC
 */
class HB_NETWORK_DECL HbServerAuthService : public HbAuthService {
    Q_OBJECT

public:
    HbServerAuthService();
    virtual ~HbServerAuthService();

    virtual void reset() override;
    const HbServiceAuthServerConfig& config() const;
    void setConfig(const HbServiceAuthServerConfig& config);

    void addStrategy(HbServerAuthStrategy* strategy);

    // From HbConnectionPool.
    virtual void onContractReceived(const HbNetworkContract* contract) override;
    virtual void onSocketConnected(networkuid socket_uid) override;
    virtual void onSocketDisconnected(networkuid socket_uid) override;
    // From HbServerAuthStrategy.
    void onAuthSucceed(networkuid socket_uid, const HbNetworkUserInfo& user_info);
    void onAuthFailed(networkuid socket_uid, HbNetworkProtocol::AuthStatus, const QString& description);

private:
    void timerEvent(QTimerEvent* event);
    bool checkSocket(networkuid socket_uid);
    void addSocket(networkuid socket_uid);
    void delSocket(networkuid socket_uid, bool delete_responses = true);
    void kickSocket(networkuid socket_uid, HbNetworkProtocol::KickCode reason, const QString& description = QString());

    HbServiceAuthServerConfig mConfig;
    QHash<authstgy, HbServerAuthStrategy*> mStrategies;
    qint32 mTimerId;

    // InOut.
    QSet<networkuid> mPendingSocket;
    QHash<networkuid, quint8> mAuthTries;
    QHash<networkuid, quint8> mAuthTimeout;
    QHash<networkuid, HbAuthStatusContract*> mResponses;
};
} // namespace network
} // namespace hb

#endif // HBSERVERAUTHSERVICE_H
