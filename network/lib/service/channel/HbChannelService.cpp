// Qt
// Hb
#include <HbLogService.h>
// Local
#include <contract/channel/HbUserSyncContract.h>
#include <service/channel/HbChannelService.h>
#include <service/channel/HbNetworkChannel.h>

using namespace hb::network;

HbChannelService::HbChannelService() {
}

void HbChannelService::reset() {
    while (!mChannels.isEmpty()) {
        HbNetworkChannel* channel = *mChannels.begin();
        unplugChannel(channel); // Handles reset.
    }

    Q_ASSERT(mChannels.size() == 0);
    mUsers.clear();
}

void HbChannelService::plugContracts(HbNetworkExchanges& exchanges) {
    exchanges.plug<HbUserSyncContract>();
}

serviceuid HbChannelService::uid() const {
    return HbNetworkProtocol::SERVICE_CHANNEL;
}

bool HbChannelService::plugChannel(HbNetworkChannel* channel, networkuid network_uid) {
    Q_ASSERT(channel);
    Q_ASSERT(channel->networkUid() == 0);

    channel->setNetworkUid(network_uid);
    serviceuid channel_uid = channel->uid();
    bool ok = false;

    if (!mChannels.contains(channel_uid)) {
        if (channel_uid < HbNetworkProtocol::SERVICE_USER) {
            qWarning() << QString("Bad range channel uid: %1 must be >= %2")
                              .arg(channel_uid)
                              .arg(HbNetworkProtocol::SERVICE_USER);
        } else {
            channel->reset();

            mChannels.insert(channel_uid, channel);
            ok = true;

            connect(channel, &HbNetworkService::contractToSend, this, &HbChannelService::onContractToSend);

            qDebug() << "Channel" << channel->uid() << "added to network" << network_uid;
        }
    } else {
        qWarning() << "Channel" << channel->uid() << "already exists";
    }

    return ok;
}

bool HbChannelService::unplugChannel(HbNetworkChannel* channel) {
    Q_ASSERT(channel);

    if (!mChannels.contains(channel->uid())) {
        qWarning() << "Channel" << channel << "inexistant";
        return false;
    }

    channel->internalReset();
    channel->reset();

    mChannels.remove(channel->uid());

    disconnect(channel, &HbNetworkService::contractToSend, this, &HbChannelService::onContractToSend);

    qDebug() << "Channel" << channel->uid() << "removed from network" << channel->networkUid();

    return true;
}

HbNetworkChannel* HbChannelService::channel(serviceuid channel_uid) {
    return mChannels.value(channel_uid, nullptr);
}

void HbChannelService::onContractToSend(const HbNetworkContract* contract) {
    Q_ASSERT(contract);

    emit contractToSend(contract);
}
