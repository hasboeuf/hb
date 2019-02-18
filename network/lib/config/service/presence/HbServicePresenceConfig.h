#ifndef HBSERVICEPRESENCECONFIG_H
#define HBSERVICEPRESENCECONFIG_H

/*! \file HbServicePresenceConfig.h */

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <config/service/HbServiceConfig.h>

namespace hb {
namespace network {

class HB_NETWORK_DECL HbServicePresenceConfig : public HbServiceConfig {
public:
    HbServicePresenceConfig();
    HbServicePresenceConfig(const HbServicePresenceConfig& config);
    virtual ~HbServicePresenceConfig() {
    } //!< \todo defaulted linux-g++ issue
    virtual HbServicePresenceConfig& operator=(const HbServicePresenceConfig& config);

    virtual bool isValid() const;

protected:
private:
};
} // namespace network
} // namespace hb

using hb::network::HbServicePresenceConfig;

#endif // HBSERVICEPRESENCECONFIG_H
