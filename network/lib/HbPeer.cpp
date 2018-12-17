// Qt
#include <QtCore/QMetaType>
// Hb
#include <HbGlobal.h>
#include <HbLogService.h>
// Local
#include <HbPeer.h>
#include <contract/HbNetworkProtocol.h>

using namespace hb::network;

HbPeer::HbPeer(const HbGeneralConfig& config, QObject* parent) : QObject(parent) {
    if (config.isValid()) {
        HbNetworkProtocol::msAppName = config.appName();
        HbNetworkProtocol::msProtocolVersion = config.protocolVersion();

        mReady = true;
    } else {
        qWarning() << "General configuration not valid. HbPeer will never do anything";
        mReady = false;
    }
}

bool HbPeer::isReady() const {
    if (!mReady) {
        qWarning() << "HbPeer not ready. Invalid config";
    }
    return mReady;
}
