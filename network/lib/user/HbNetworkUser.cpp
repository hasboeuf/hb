// Qt
// Hb
// Local
#include <user/HbNetworkUser.h>

using namespace hb::network;

HbNetworkUser::HbNetworkUser(QObject* parent) : QObject(parent) {
    mMainSocket = 0;
    mInfo = ShConstHbNetworkUserInfo(
        new HbNetworkUserInfo()); // Valid object instead of nullptr to avoid checking ptr everytime.
}

void HbNetworkUser::reset() {
    mMainSocket = 0;
    mInfo.clear();
    mInfo = ShConstHbNetworkUserInfo(
        new HbNetworkUserInfo()); // Valid object instead of nullptr to avoid checking ptr everytime.
}

ShConstHbNetworkUserInfo& HbNetworkUser::info() {
    return mInfo;
}

void HbNetworkUser::setInfo(const HbNetworkUserInfo& user_info) {
    mInfo.clear();
    mInfo = ShConstHbNetworkUserInfo(new HbNetworkUserInfo(user_info));
}

networkuid HbNetworkUser::mainSocketUid() const {
    return mMainSocket;
}
