// Local
#include <config/service/channel/HbServiceChannelClientConfig.h>

using namespace hb::network;

HbServiceChannelClientConfig::HbServiceChannelClientConfig() : HbServiceChannelConfig() {
}

HbServiceChannelClientConfig::HbServiceChannelClientConfig(const HbServiceChannelClientConfig& config) :
        HbServiceChannelConfig(config) {
    if (this != &config) {
    }
}

HbServiceChannelClientConfig& HbServiceChannelClientConfig::operator=(const HbServiceChannelClientConfig& config) {
    if (this != &config) {
        HbServiceChannelConfig::operator=(config);
    }

    return *this;
}

bool HbServiceChannelClientConfig::isValid() const {
    return HbServiceChannelConfig::isValid();
}
