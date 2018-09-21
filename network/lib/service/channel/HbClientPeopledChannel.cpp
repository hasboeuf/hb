// Local
#include <service/channel/HbClientPeopledChannel.h>

using namespace hb::network;

void HbClientPeopledChannel::internalReset(bool keep_uid) {
    HbNetworkChannel::internalReset(keep_uid);

    // Clean users.
    for (ShConstHbNetworkUserInfo user_info : mUsers.values()) {
        emit userDisconnected(user_info);
    }
    mUsers.clear();
}

void HbClientPeopledChannel::onUserConnected(ShConstHbNetworkUserInfo user_info) {
    mUsers.insert(user_info->email(), user_info);
    emit userConnected(user_info);
}

void HbClientPeopledChannel::onUserDisconnected(ShConstHbNetworkUserInfo user_info) {
    mUsers.remove(user_info->email());
    emit userDisconnected(user_info);
}

const QHash<QString, ShConstHbNetworkUserInfo>& HbClientPeopledChannel::connectedUsers() const {
    return mUsers;
}
