#ifndef HBSERVICECONFIG_H
#define HBSERVICECONFIG_H

/*! \file HbServiceConfig.h */

// Qt
// Hb
// Local
#include <HbNetwork.h>

namespace hb {
namespace network {

class HB_NETWORK_DECL HbServiceConfig {
public:
    HbServiceConfig();
    HbServiceConfig(const HbServiceConfig& config);
    virtual ~HbServiceConfig() {
    } //!< \todo defaulted linux-g++ issue
    virtual HbServiceConfig& operator=(const HbServiceConfig& config);

    virtual bool isValid() const;

protected:
private:
};
} // namespace network
} // namespace hb

using hb::network::HbServiceConfig;

#endif // HBSERVICECONFIG_H
