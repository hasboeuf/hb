// Qt
// Hb
// Local
#include <user/HbClientUser.h>

using namespace hb::network;

HbClientUser::HbClientUser(QObject* parent) : HbNetworkUser(parent) {
    setStatus(HbNetworkProtocol::USER_DISCONNECTED);
}

void HbClientUser::reset() {
    HbNetworkUser::reset();
    setStatus(HbNetworkProtocol::USER_DISCONNECTED);
}

HbNetworkProtocol::UserStatus HbClientUser::status() const {
    return mStatus;
}

void HbClientUser::setStatus(HbNetworkProtocol::UserStatus status) {
    if (mStatus != status) {
        mStatus = status;
        emit statusChanged(status);
    }
}

void HbClientUser::addSocket(networkuid socket_uid, bool main) {
    Q_ASSERT(!mSocketsUid.contains(socket_uid));

    if (main) {
        Q_ASSERT(mMainSocket == 0);
        mMainSocket = socket_uid;
        setStatus(HbNetworkProtocol::USER_CONNECTING);
    }
}

void HbClientUser::delSocket(networkuid socket_uid) {
    Q_ASSERT(mSocketsUid.contains(socket_uid));
    mSocketsUid.removeOne(socket_uid);
}

QList<networkuid> HbClientUser::socketsUid() const {
    return mSocketsUid;
}
