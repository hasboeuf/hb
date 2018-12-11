// Qt
// Hb
#include <HbLogService.h>
// Local
#include <contract/presence/HbPresenceContract.h>
#include <service/presence/HbServerPresenceService.h>

using namespace hb::network;

HbServerPresenceService::HbServerPresenceService() {
    mTickTimer = 0;
}

void HbServerPresenceService::reset() {
    if (mTickTimer > 0) {
        killTimer(mTickTimer);
        mTickTimer = 0;
    }

    mClientAliveTick.clear();
}

const HbServicePresenceServerConfig& HbServerPresenceService::config() const {
    return mConfig;
}

void HbServerPresenceService::setConfig(const HbServicePresenceServerConfig& config) {
    if (config.isValid()) {
        mConfig = config;
    }
}

void HbServerPresenceService::timerEvent(QTimerEvent*) {
    auto it = mClientAliveTick.begin();
    while (it != mClientAliveTick.end()) {
        networkuid socket_uid = it.key();
        quint16 last_presence = ++(it.value()); // Add one second to the last presence.

        if (last_presence == mConfig.kickAliveThreshold()) // Emit kick only once.
        {
            emit socketToKick(socket_uid,
                              HbNetworkProtocol::KICK_PRESENCE_TIMEOUT,
                              QString("Not alive since %1 second(s)").arg(last_presence));
        } else if (last_presence >= mConfig.warningAliveThreshold()) {
            emit socketLagged(socket_uid, last_presence, mConfig.kickAliveThreshold());
        }

        ++it;
    }
}

void HbServerPresenceService::onSocketAuthenticated(networkuid socket_uid) {
    Q_ASSERT(!mClientAliveTick.contains(socket_uid));

    if (mTickTimer == 0) // No timer started yet.
    {
        mTickTimer = startTimer(1000);
    }

    mClientAliveTick.insert(socket_uid, 0);
}

void HbServerPresenceService::onSocketUnauthenticated(networkuid socket_uid) {
    Q_ASSERT(mClientAliveTick.contains(socket_uid));

    mClientAliveTick.remove(socket_uid);

    if (mClientAliveTick.size() == 0) // No clients => stop the timer.
    {
        killTimer(mTickTimer);
        mTickTimer = 0;
    }
}

void HbServerPresenceService::onContractReceived(const HbNetworkContract* contract) {
    const HbPresenceContract* presence_contract = contract->value<HbPresenceContract>();
    if (presence_contract) {
        networkuid socket_uid = presence_contract->sender();

        Q_ASSERT(mClientAliveTick.contains(socket_uid));
        mClientAliveTick[socket_uid] = 0; // Update client tick.
    } else {
        qWarning() << "Presence contract type not recognized";
        //! \todo How to kick?
    }

    delete presence_contract;
}
