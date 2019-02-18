#ifndef HBSERVICECHANNELCONFIG_H
#define HBSERVICECHANNELCONFIG_H

/*! \file HbServiceChannelConfig.h */

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <config/service/HbServiceConfig.h>

namespace hb {
namespace network {

class HB_NETWORK_DECL HbServiceChannelConfig : public HbServiceConfig {
public:
    HbServiceChannelConfig();
    HbServiceChannelConfig(const HbServiceChannelConfig& config);
    virtual ~HbServiceChannelConfig() {
    } //!< \todo defaulted linux-g++ issue
    virtual HbServiceChannelConfig& operator=(const HbServiceChannelConfig& config);

    virtual bool isValid() const;

protected:
private:
};
} // namespace network
} // namespace hb

using hb::network::HbServiceChannelConfig;

#endif // HBSERVICECHANNELCONFIG_H
