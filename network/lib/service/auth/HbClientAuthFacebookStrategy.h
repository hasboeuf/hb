#ifndef HBCLIENTAUTHFACEBOOKSTRATEGY_H
#define HBCLIENTAUTHFACEBOOKSTRATEGY_H

/*! \file HbClientAuthFacebookStrategy.h */

// Qt
#include <QtCore/QHash>
// Hb
#include <facebook/HbO2ClientFacebook.h>
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
class HB_NETWORK_DECL HbClientAuthFacebookStrategy : public HbClientOAuthStrategy {
    Q_OBJECT
public:
    HbClientAuthFacebookStrategy() = default;
    virtual ~HbClientAuthFacebookStrategy() = default;

    virtual void reset() override;

    virtual void setConfig(const HbO2ClientConfig& config) override;

    virtual authstgy type() const;

    virtual bool prepareAuthContract(HbClientAuthLoginObject* login_object) override;
};
} // namespace network
} // namespace hb

using hb::network::HbClientAuthFacebookStrategy;

#endif // HBCLIENTAUTHFACEBOOKSTRATEGY_H
