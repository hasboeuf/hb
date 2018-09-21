// Qt
// Hb
// Local
#include <user/HbServerUser.h>

using namespace hb::network;

HbServerUser::HbServerUser() : HbNetworkUser() {
}

void HbServerUser::addSocket(networkuid server_uid, networkuid socket_uid, bool main) {
    mSocketsByServer.insert(server_uid, socket_uid);

    if (main) {
        mMainSocket = socket_uid;
    }
}

void HbServerUser::delSocket(networkuid socket_uid) {
    mSocketsByServer.remove(mSocketsByServer.key(socket_uid, 0));
    if (socket_uid == mMainSocket) {
        mMainSocket = 0;
    }
}

networkuid HbServerUser::socketUid(networkuid server_uid) {
    return mSocketsByServer.value(server_uid, mMainSocket);
}

QList<networkuid> HbServerUser::socketsUid() const {
    return mSocketsByServer.values();
}
