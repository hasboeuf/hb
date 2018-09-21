// Local
#include <com/HbAbstractNetwork.h>
#include <contract/HbNetworkContract.h>

using namespace hb::network;

HbAbstractNetwork::HbAbstractNetwork(QObject* parent) : QObject(parent) {
    qRegisterMetaType<networkuid>("networkuid");
    qRegisterMetaType<serviceuid>("serviceuid");
    qRegisterMetaType<codeuid>("codeuid");
    qRegisterMetaType<contractuid>("contractuid");
    qRegisterMetaType<ShConstHbNetworkContract>("ShConstHbNetworkContract");
    qRegisterMetaType<ShHbNetworkContract>("ShHbNetworkContract");
    qRegisterMetaType<HbNetworkUserInfo>("HbNetworkUserInfo");
    qRegisterMetaType<ShConstHbNetworkUserInfo>("ShConstHbNetworkUserInfo");
    qRegisterMetaType<ShHbNetworkUserInfo>("ShHbNetworkUserInfo");
}

const HbNetworkConfig& HbAbstractNetwork::configuration() const {
    return mConfig;
}

bool HbAbstractNetwork::checkHeader(const HbNetworkHeader& header) {
    if ((header.appName() != HbNetworkProtocol::msAppName)
        || (header.protocolVersion() != HbNetworkProtocol::msProtocolVersion)) {
        return false;
    }

    return true;
}
