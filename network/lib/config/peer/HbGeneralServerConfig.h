#ifndef HBGENERALSERVERCONFIG_H
#define HBGENERALSERVERCONFIG_H

/*! \file HbGeneralServerConfig.h */

// Qt
#include <QtCore/QHash>
#include <QtCore/QString>
// Hb
// Local
#include <HbNetwork.h>
#include <config/peer/HbGeneralConfig.h>
#include <config/service/auth/HbServiceAuthServerConfig.h>
#include <config/service/channel/HbServiceChannelServerConfig.h>
#include <config/service/presence/HbServicePresenceServerConfig.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbGeneralServerConfig : public HbGeneralConfig {
public:
    HbGeneralServerConfig() = default;
    HbGeneralServerConfig(const HbGeneralServerConfig& config);
    virtual ~HbGeneralServerConfig() = default;
    virtual HbGeneralServerConfig& operator=(const HbGeneralServerConfig& config);

    virtual bool isValid() const;

    HbServiceAuthServerConfig& auth();
    HbServiceChannelServerConfig& channel();
    HbServicePresenceServerConfig& presence();

    const HbServiceAuthServerConfig& auth() const;
    const HbServiceChannelServerConfig& channel() const;
    const HbServicePresenceServerConfig& presence() const;

protected:
private:
    HbServiceAuthServerConfig mAuthConfig;
    HbServiceChannelServerConfig mChannelConfig;
    HbServicePresenceServerConfig mPresenceConfig;
};
} // namespace network
} // namespace hb

using hb::network::HbGeneralServerConfig;

#endif // HBGENERALSERVERCONFIG_H
