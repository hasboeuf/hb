// Qt
// Hb
#include <HbLogService.h>
// Local
#include <contract/channel/HbUserSyncContract.h>
#include <service/channel/HbClientChannel.h>
#include <service/channel/HbClientChannelService.h>
#include <service/channel/HbClientPeopledChannel.h>

using namespace hb::network;

void HbClientChannelService::reset() {
    HbChannelService::reset(); // Handles channels unplugging.
    Q_ASSERT(mPeopledChannels.size() == 0);
}

const HbServiceChannelClientConfig& HbClientChannelService::config() const {
    return mConfig;
}

void HbClientChannelService::setConfig(const HbServiceChannelClientConfig& config) {
    if (config.isValid()) {
        mConfig = config;
    }
}

bool HbClientChannelService::plugChannel(HbNetworkChannel* channel, networkuid network_uid) {
    bool ok = false;

    if (dynamic_cast<HbClientChannel*>(channel)) {
        ok = HbChannelService::plugChannel(channel, network_uid);

        Q_ASSERT(channel->networkUid() != 0);

        if (ok) {
            HbClientPeopledChannel* peopled_channel = dynamic_cast<HbClientPeopledChannel*>(channel);
            if (peopled_channel) {
                mPeopledChannels.insert(peopled_channel->uid(), peopled_channel);

                connect(this,
                        &HbClientChannelService::userConnected,
                        peopled_channel,
                        &HbClientPeopledChannel::onUserConnected);
                connect(this,
                        &HbClientChannelService::userDisconnected,
                        peopled_channel,
                        &HbClientPeopledChannel::onUserDisconnected);
            }
        }
    }

    return ok;
}

bool HbClientChannelService::unplugChannel(HbNetworkChannel* channel) {
    bool ok = HbChannelService::unplugChannel(channel);

    if (ok) {
        HbClientPeopledChannel* peopled_channel = mPeopledChannels.value(channel->uid(), nullptr);
        if (peopled_channel) {
            disconnect(this,
                       &HbClientChannelService::userConnected,
                       peopled_channel,
                       &HbClientPeopledChannel::onUserConnected);
            disconnect(this,
                       &HbClientChannelService::userDisconnected,
                       peopled_channel,
                       &HbClientPeopledChannel::onUserDisconnected);

            mPeopledChannels.remove(peopled_channel->uid());
        }
    }

    return ok;
}

HbClientChannel* HbClientChannelService::channel(serviceuid channel_uid) {
    return dynamic_cast<HbClientChannel*>(HbChannelService::channel(channel_uid));
}

void HbClientChannelService::onUserContractReceived(const HbNetworkContract* contract) {
    Q_ASSERT(contract);

    serviceuid channel_uid = contract->header().service();

    // Internal contract.
    if (channel_uid == uid()) {
        processContract(contract);
        return;
    }

    // Channel contract.

    HbClientChannel* channel = this->channel(channel_uid);
    if (!channel) {
        qWarning() << "Null channel" << channel_uid;
        delete contract;
        return;
    }

    channel->onUserContractReceived(contract);
}

void HbClientChannelService::onUserConnected(ShConstHbNetworkUserInfo user_info) {
    emit userConnected(user_info);
}

void HbClientChannelService::onUserDisconnected(ShConstHbNetworkUserInfo user_info) {
    emit userDisconnected(user_info);
}

void HbClientChannelService::processContract(const HbNetworkContract* contract) {
    Q_ASSERT(contract);

    const HbUserSyncContract* sync_contract = contract->value<HbUserSyncContract>();
    if (sync_contract) {
        for (HbNetworkUserSync user_sync : sync_contract->syncs()) {
            ShConstHbNetworkUserInfo user_info(new HbNetworkUserInfo(user_sync.userInfo()));
            if (user_sync.status() == HbNetworkProtocol::NETWORK_USER_CONNECTED) {
                mUsers.insert(user_info->email(), user_info);
                onUserConnected(user_info); // Simulates user connection.
            } else if (user_sync.status() == HbNetworkProtocol::NETWORK_USER_DISCONNECTED) {
                mUsers.remove(user_info->email());
                onUserDisconnected(user_info); // Simulates user disconnection.
            } else {
                qWarning() << "User status not recognized";
            }
        }
    } else {
        qWarning() << "Channel contract type not recognized";
        //! \todo How to kick?
    }

    delete contract;
}
