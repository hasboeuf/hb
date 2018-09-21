// Hb
#include <HbLogService.h>
// Local
#include <config/service/presence/HbServicePresenceClientConfig.h>

using namespace hb::network;

HbServicePresenceClientConfig::HbServicePresenceClientConfig() : HbServicePresenceConfig() {
    mKeepAliveInterval = 0;
}

HbServicePresenceClientConfig::HbServicePresenceClientConfig(const HbServicePresenceClientConfig& config) :
        HbServicePresenceConfig(config) {
    if (this != &config) {
        mKeepAliveInterval = config.mKeepAliveInterval;
    }
}

HbServicePresenceClientConfig& HbServicePresenceClientConfig::operator=(const HbServicePresenceClientConfig& config) {
    if (this != &config) {
        HbServicePresenceConfig::operator=(config);

        mKeepAliveInterval = config.mKeepAliveInterval;
    }

    return *this;
}

bool HbServicePresenceClientConfig::isValid() const {
    if (!HbServicePresenceConfig::isValid()) {
        return false;
    }

    if (mKeepAliveInterval == 0) {
        qWarning() << "KeepAliveInterval must be > 0";
        return true;
    }

    return true;
}

void HbServicePresenceClientConfig::setKeepAliveInterval(quint16 interval) {
    mKeepAliveInterval = interval;
}

quint16 HbServicePresenceClientConfig::keepAliveInterval() const {
    return mKeepAliveInterval;
}
