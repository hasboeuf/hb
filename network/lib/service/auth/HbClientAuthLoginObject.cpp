#include <service/auth/HbClientAuthLoginObject.h>

using namespace hb::network;

HbClientAuthLoginObject::HbClientAuthLoginObject() {
    mStrategy = HbAuthService::AUTH_NONE;
    mSocketUid = 0;
}

void HbClientAuthLoginObject::setStrategy(authstgy strategy) {
    if (strategy != HbAuthService::AUTH_NONE) {
        mStrategy = strategy;
    }
}

void HbClientAuthLoginObject::setSocketUid(networkuid socket_uid) {
    if (socket_uid != 0) {
        mSocketUid = socket_uid;
    }
}

authstgy HbClientAuthLoginObject::strategy() const {
    return mStrategy;
}

networkuid HbClientAuthLoginObject::socketUid() const {
    return mSocketUid;
}
