// Local
#include <config/service/presence/HbServicePresenceConfig.h>

using namespace hb::network;

HbServicePresenceConfig::HbServicePresenceConfig() : HbServiceConfig() {
}

HbServicePresenceConfig::HbServicePresenceConfig(const HbServicePresenceConfig& config) : HbServiceConfig(config) {
    if (this != &config) {
    }
}

HbServicePresenceConfig& HbServicePresenceConfig::operator=(const HbServicePresenceConfig& config) {
    if (this != &config) {
        HbServiceConfig::operator=(config);
    }

    return *this;
}

bool HbServicePresenceConfig::isValid() const {
    return HbServiceConfig::isValid();
}
