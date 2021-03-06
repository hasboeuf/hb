// Local
#include <contract/HbNetworkProtocol.h>
#include <contract/presence/HbPresenceContract.h>

HbPresenceContract::HbPresenceContract() :
        HbNetworkContract(HbNetworkProtocol::SERVICE_PRESENCE, HbNetworkProtocol::CODE_CLT_PRESENCE) {
    setRouting(HbNetworkProtocol::ROUTING_UNICAST);
}

HbPresenceContract::HbPresenceContract(const HbPresenceContract& source) : HbNetworkContract(source) {
    if (&source != this) {
    }
}

HbPresenceContract& HbPresenceContract::operator=(const HbPresenceContract& source) {
    if (&source != this) {
        HbNetworkContract::operator=(source);
    }

    return (*this);
}

HbPresenceContract* HbPresenceContract::create() const {
    return new HbPresenceContract();
}

bool HbPresenceContract::read(QDataStream& stream) {
    Q_UNUSED(stream)

    return true;
}

bool HbPresenceContract::write(QDataStream& stream) const {
    Q_UNUSED(stream)

    return true;
}
