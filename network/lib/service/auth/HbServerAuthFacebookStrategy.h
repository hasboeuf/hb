#ifndef HBSERVERAUTHFACEBOOKSTRATEGY_H
#define HBSERVERAUTHFACEBOOKSTRATEGY_H

/*! \file HbServerAuthFacebookStrategy.h */

// Qt
#include <QtCore/QHash>
// Hb
#include <config/HbO2ServerConfig.h>
#include <facebook/HbFacebookRequester.h>
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkProtocol.h>
#include <contract/auth/HbAuthRequestContract.h> // Template.
#include <service/auth/HbServerOAuthStrategy.h>

namespace hb {
using namespace link;

namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbServerAuthFacebookStrategy : public HbServerOAuthStrategy {
    Q_OBJECT
public:
    HbServerAuthFacebookStrategy();
    virtual ~HbServerAuthFacebookStrategy() = default;

    virtual authstgy type() const;
    virtual bool checkLogin(const HbAuthRequestContract* contract) override;

    void onLinkSucceed();
    void onRequestCompleted(quint64 request_id, HbFacebookObject* object);

private:
    HbFacebookRequester mRequester;
};
} // namespace network
} // namespace hb

using hb::network::HbServerAuthFacebookStrategy;

#endif // HBSERVERAUTHFACEBOOKSTRATEGY_H
