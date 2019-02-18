#ifndef HBSERVICECHANNELSERVERCONFIG_H
#define HBSERVICECHANNELSERVERCONFIG_H

/*! \file HbServiceChannelServerConfig.h */

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <config/service/channel/HbServiceChannelConfig.h>

namespace hb {
namespace network {

class HB_NETWORK_DECL HbServiceChannelServerConfig : public HbServiceChannelConfig {
public:
    HbServiceChannelServerConfig();
    HbServiceChannelServerConfig(const HbServiceChannelServerConfig& config);
    virtual ~HbServiceChannelServerConfig() = default;
    virtual HbServiceChannelServerConfig& operator=(const HbServiceChannelServerConfig& config);

    virtual bool isValid() const;

protected:
private:
};
} // namespace network
} // namespace hb

using hb::network::HbServiceChannelServerConfig;

#endif // HBSERVICECHANNELSERVERCONFIG_H
