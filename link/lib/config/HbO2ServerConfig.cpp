// Local
#include <config/HbO2ServerConfig.h>

using namespace hb::link;

HbO2ServerConfig::HbO2ServerConfig(const HbO2ServerConfig& config) : HbO2Config(config) {
    if (this != &config) {
        mClientSecret = config.mClientSecret;
    }
}

HbO2ServerConfig& HbO2ServerConfig::operator=(const HbO2ServerConfig& config) {
    if (this != &config) {
        HbO2Config::operator=(config);

        mClientSecret = config.mClientSecret;
    }

    return *this;
}

bool HbO2ServerConfig::isValid() const {
    if (HbO2Config::isValid()) {
        return (!mClientSecret.isEmpty());
    }
    return false;
}

bool HbO2ServerConfig::read(QDataStream& stream) {
    stream >> mClientSecret;

    return true;
}

bool HbO2ServerConfig::write(QDataStream& stream) const {
    stream << mClientSecret;

    return true;
}

void HbO2ServerConfig::setClientSecret(const QString& client_secret) {
    if (!client_secret.isEmpty()) {
        mClientSecret = client_secret;
    }
}

const QString& HbO2ServerConfig::clientSecret() const {
    return mClientSecret;
}
