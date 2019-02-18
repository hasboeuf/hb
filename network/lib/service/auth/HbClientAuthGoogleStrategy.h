#ifndef HBCLIENTAUTHGOOGLESTRATEGY_H
#define HBCLIENTAUTHGOOGLESTRATEGY_H

// Qt
#include <QtCore/QHash>
// Hb
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkProtocol.h>
#include <contract/auth/HbAuthRequestContract.h> // Template.
#include <service/auth/HbClientOAuthStrategy.h>

namespace hb {
using namespace link;

namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbClientAuthGoogleStrategy : public HbClientOAuthStrategy {
    Q_OBJECT
public:
    HbClientAuthGoogleStrategy() = default;
    virtual ~HbClientAuthGoogleStrategy() = default;

    virtual void reset() override;

    virtual void setConfig(const HbO2ClientConfig& config) override;

    virtual authstgy type() const;

    virtual bool prepareAuthContract(HbClientAuthLoginObject* login_object) override;
};
} // namespace network
} // namespace hb

using hb::network::HbClientAuthGoogleStrategy;

#endif // HBCLIENTAUTHGOOGLESTRATEGY_H
