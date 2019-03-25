// Local
#include <config/HbO2Config.h>

using namespace hb::link;

HbO2Config::HbO2Config(const HbO2Config& config) {
    if (this != &config) {
        mClientId = config.mClientId;
    }
}

HbO2Config& HbO2Config::operator=(const HbO2Config& config) {
    if (this != &config) {
        mClientId = config.mClientId;
    }

    return *this;
}

bool HbO2Config::isValid() const {
    return (!mClientId.isEmpty());
}

QString HbO2Config::clientId() const {
    return mClientId;
}

void HbO2Config::setClientId(const QString& client_id) {
    if (!client_id.isEmpty()) {
        mClientId = client_id;
    }
}

namespace hb {
namespace link {

QDataStream& operator<<(QDataStream& stream, const HbO2Config& config) {
    // stream << config.mClientId; ClientId is also set on server side.
    config.write(stream);

    return stream;
}

QDataStream& operator>>(QDataStream& stream, HbO2Config& config) {
    // stream >> config.mClientId; ClientId is also set on server side.
    config.read(stream);

    return stream;
}
} // namespace link
} // namespace hb
