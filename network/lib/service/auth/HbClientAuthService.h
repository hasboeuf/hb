/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCLIENTAUTHSERVICE_H
#define HBCLIENTAUTHSERVICE_H

/*! \file HbClientAuthService.h */

// Qt
// Hb
// Local
#include <config/service/auth/HbServiceAuthClientConfig.h>
#include <service/auth/HbAuthService.h>

namespace hb {
namespace network {
class HbClientAuthStrategy;
class HbClientAuthLoginObject;
class HbAuthRequestContract;

/*!
 * TODOC
 */
class HB_NETWORK_DECL HbClientAuthService : public HbAuthService {
    Q_OBJECT

public:
    HbClientAuthService();
    virtual ~HbClientAuthService() = default;

    virtual void reset() override;
    const HbServiceAuthClientConfig& config() const;
    void setConfig(const HbServiceAuthClientConfig& config);

    void addStrategy(HbClientAuthStrategy* strategy);

    virtual void onContractReceived(const HbNetworkContract* contract) override;
    virtual void onSocketConnected(networkuid socket_uid) override;
    virtual void onSocketDisconnected(networkuid socket_uid) override;

    // From ClientConnectionPool.
    void onAuthRequested(HbClientAuthLoginObject* login_object);

    // From HbClientAuthStrategy.
    void onAuthContractReady(networkuid socket_uid, HbAuthRequestContract* contract);
    void onAuthContractFailed(networkuid socket_uid, const QString& description);

private:
    networkuid mPendingSocket;
    HbServiceAuthClientConfig mConfig;
    QHash<authstgy, HbClientAuthStrategy*> mStrategies;
};
} // namespace network
} // namespace hb

#endif // HBCLIENTAUTHSERVICE_H
