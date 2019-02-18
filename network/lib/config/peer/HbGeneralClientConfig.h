#ifndef HBGENERALCLIENTCONFIG_H
#define HBGENERALCLIENTCONFIG_H

/*! \file HbGeneralClientConfig.h */

// Qt
#include <QtCore/QHash>
#include <QtCore/QString>
// Hb
// Local
#include <HbNetwork.h>
#include <config/peer/HbGeneralConfig.h>
#include <config/service/auth/HbServiceAuthClientConfig.h>
#include <config/service/channel/HbServiceChannelClientConfig.h>
#include <config/service/presence/HbServicePresenceClientConfig.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbGeneralClientConfig : public HbGeneralConfig {
public:
    HbGeneralClientConfig() = default;
    HbGeneralClientConfig(const HbGeneralClientConfig& config);
    virtual ~HbGeneralClientConfig() = default;
    virtual HbGeneralClientConfig& operator=(const HbGeneralClientConfig& config);

    virtual bool isValid() const;

    HbServiceAuthClientConfig& auth();
    HbServiceChannelClientConfig& channel();
    HbServicePresenceClientConfig& presence();

    const HbServiceAuthClientConfig& auth() const;
    const HbServiceChannelClientConfig& channel() const;
    const HbServicePresenceClientConfig& presence() const;

protected:
private:
    HbServiceAuthClientConfig mAuthConfig;
    HbServiceChannelClientConfig mChannelConfig;
    HbServicePresenceClientConfig mPresenceConfig;
};
} // namespace network
} // namespace hb

using hb::network::HbGeneralClientConfig;

#endif // HBGENERALCLIENTCONFIG_H
