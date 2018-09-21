// Local
#include <config/service/channel/HbServiceChannelConfig.h>

using namespace hb::network;

HbServiceChannelConfig::HbServiceChannelConfig() : HbServiceConfig() {
}

HbServiceChannelConfig::HbServiceChannelConfig(const HbServiceChannelConfig& config) : HbServiceConfig(config) {
    if (this != &config) {
    }
}

HbServiceChannelConfig& HbServiceChannelConfig::operator=(const HbServiceChannelConfig& config) {
    if (this != &config) {
        HbServiceConfig::operator=(config);
    }

    return *this;
}

bool HbServiceChannelConfig::isValid() const {
    return HbServiceConfig::isValid();
}
