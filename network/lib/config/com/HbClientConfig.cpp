// Local
#include <config/com/HbClientConfig.h>

HbClientConfig::HbClientConfig() : HbNetworkConfig() {
    mReconnectionDelay = 0;
}

HbClientConfig::HbClientConfig(const HbClientConfig& config) : HbNetworkConfig(config) {
    if (&config != this) {
        mReconnectionDelay = config.mReconnectionDelay;
    }
}

HbClientConfig& HbClientConfig::operator=(const HbClientConfig& config) {
    if (&config != this) {
        HbNetworkConfig::operator=(config);

        mReconnectionDelay = config.mReconnectionDelay;
    }
    return (*this);
}

bool HbClientConfig::isValid() const {
    if (!HbNetworkConfig::isValid()) {
        return false;
    }

    return true;
}

void HbClientConfig::setReconnectionDelay(quint16 duration) {
    mReconnectionDelay = duration;
}

quint16 HbClientConfig::reconnectionDelay() const {
    return mReconnectionDelay;
}
