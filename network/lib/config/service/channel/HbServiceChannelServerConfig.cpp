// Local
#include <config/service/channel/HbServiceChannelServerConfig.h>

using namespace hb::network;

HbServiceChannelServerConfig::HbServiceChannelServerConfig() : HbServiceChannelConfig() {
}

HbServiceChannelServerConfig::HbServiceChannelServerConfig(const HbServiceChannelServerConfig& config) :
        HbServiceChannelConfig(config) {
    if (this != &config) {
    }
}

HbServiceChannelServerConfig& HbServiceChannelServerConfig::operator=(const HbServiceChannelServerConfig& config) {
    if (this != &config) {
        HbServiceChannelConfig::operator=(config);
    }

    return *this;
}

bool HbServiceChannelServerConfig::isValid() const {
    return HbServiceChannelConfig::isValid();
}
