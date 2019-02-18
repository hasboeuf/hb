#ifndef HBSERVERAUTHSTRATEGY_H
#define HBSERVERAUTHSTRATEGY_H

/*! \file HbServerAuthStrategy.h */

// Qt
// Hb
// Local
#include <contract/auth/HbAuthRequestContract.h> // Template.
#include <service/auth/HbAuthStrategy.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbServerAuthStrategy : public HbAuthStrategy {
    Q_OBJECT
public:
    HbServerAuthStrategy() = default;
    virtual ~HbServerAuthStrategy() = default;

    virtual bool checkLogin(const HbAuthRequestContract* contract) = 0;

signals:
    void authSucceed(networkuid sender, const HbNetworkUserInfo& user_info);
    void authFailed(networkuid sender, const HbNetworkProtocol::AuthStatus& status, const QString& description);
};
} // namespace network
} // namespace hb

using hb::network::HbServerAuthStrategy;

#endif // HBSERVERAUTHSTRATEGY_H
