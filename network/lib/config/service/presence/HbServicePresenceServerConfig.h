#ifndef HBSERVICEPRESENCESERVERCONFIG_H
#define HBSERVICEPRESENCESERVERCONFIG_H

/*! \file HbServicePresenceServerConfig.h */

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <config/service/presence/HbServicePresenceConfig.h>

namespace hb {
namespace network {

class HB_NETWORK_DECL HbServicePresenceServerConfig : public HbServicePresenceConfig {
public:
    HbServicePresenceServerConfig();
    HbServicePresenceServerConfig(const HbServicePresenceServerConfig& config);
    virtual ~HbServicePresenceServerConfig() = default;
    virtual HbServicePresenceServerConfig& operator=(const HbServicePresenceServerConfig& config);

    virtual bool isValid() const;

    virtual void setWarningAliveThreshold(quint16 threshold);
    virtual quint16 warningAliveThreshold() const;

    virtual void setKickAliveThreshold(quint16 threshold);
    virtual quint16 kickAliveThreshold() const;

protected:
private:
    quint16 mWarningAliveThreshold;
    quint16 mKickAliveThreshold;
};
} // namespace network
} // namespace hb

using hb::network::HbServicePresenceServerConfig;

#endif // HBSERVICEPRESENCESERVERCONFIG_H
