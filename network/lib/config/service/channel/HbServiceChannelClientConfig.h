#ifndef HBSERVICECHANNELCLIENTCONFIG_H
#define HBSERVICECHANNELCLIENTCONFIG_H

/*! \file HbServiceChannelClientConfig.h */

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <config/service/channel/HbServiceChannelConfig.h>

namespace hb {
namespace network {

class HB_NETWORK_DECL HbServiceChannelClientConfig : public HbServiceChannelConfig {
public:
    HbServiceChannelClientConfig();
    HbServiceChannelClientConfig(const HbServiceChannelClientConfig& config);
    virtual ~HbServiceChannelClientConfig() {
    } //!< \todo defaulted linux-g++ issue
    virtual HbServiceChannelClientConfig& operator=(const HbServiceChannelClientConfig& config);

    virtual bool isValid() const;

protected:
private:
};
} // namespace network
} // namespace hb

using hb::network::HbServiceChannelClientConfig;

#endif // HBSERVICECHANNELCLIENTCONFIG_H
