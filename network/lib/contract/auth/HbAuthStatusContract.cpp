// Local
#include <contract/HbNetworkProtocol.h>
#include <contract/auth/HbAuthStatusContract.h>

using namespace hb::network;

HbAuthStatusContract::HbAuthStatusContract() :
        HbNetworkContract(HbNetworkProtocol::SERVICE_AUTH, HbNetworkProtocol::CODE_SRV_AUTH_STATUS) {
    setRouting(HbNetworkProtocol::ROUTING_UNICAST);
    mStatus = HbNetworkProtocol::AUTH_BAD;
    mTryNumber = 0;
    mMaxTries = 0;
}

HbAuthStatusContract::HbAuthStatusContract(const HbAuthStatusContract& source) : HbNetworkContract(source) {
    if (&source != this) {
        mUserInfo = source.mUserInfo;
        mStatus = source.mStatus;
        mDescription = source.mDescription;
        mTryNumber = source.mTryNumber;
        mMaxTries = source.mMaxTries;
    }
}

HbAuthStatusContract& HbAuthStatusContract::operator=(const HbAuthStatusContract& source) {
    if (&source != this) {
        HbNetworkContract::operator=(source);

        mUserInfo = source.mUserInfo;
        mStatus = source.mStatus;
        mDescription = source.mDescription;
        mTryNumber = source.mTryNumber;
        mMaxTries = source.mMaxTries;
    }

    return (*this);
}

HbAuthStatusContract* HbAuthStatusContract::create() const {
    return new HbAuthStatusContract();
}

bool HbAuthStatusContract::read(QDataStream& stream) {
    stream >> mUserInfo;
    netwint status;
    stream >> status;
    stream >> mDescription;
    stream >> mTryNumber;
    stream >> mMaxTries;

    mStatus = (HbNetworkProtocol::AuthStatus)status;

    return true;
}

bool HbAuthStatusContract::write(QDataStream& stream) const {
    stream << mUserInfo;
    stream << (netwint)mStatus;
    stream << mDescription;
    stream << mTryNumber;
    stream << mMaxTries;

    return true;
}

void HbAuthStatusContract::setUserInfo(const HbNetworkUserInfo& user_info) {
    mUserInfo = user_info;
}

void HbAuthStatusContract::setStatus(HbNetworkProtocol::AuthStatus status) {
    mStatus = status;
}

void HbAuthStatusContract::setDescription(const QString& description) {
    mDescription = description;
}

void HbAuthStatusContract::setTryNumber(quint8 try_number) {
    mTryNumber = try_number;
}

void HbAuthStatusContract::setMaxTries(quint8 max_tries) {
    mMaxTries = max_tries;
}

const HbNetworkUserInfo& HbAuthStatusContract::userInfo() const {
    return mUserInfo;
}

HbNetworkUserInfo& HbAuthStatusContract::userInfo() {
    return mUserInfo;
}

HbNetworkProtocol::AuthStatus HbAuthStatusContract::status() const {
    return mStatus;
}

QString HbAuthStatusContract::description() const {
    return mDescription;
}

quint8 HbAuthStatusContract::tryNumber() const {
    return mTryNumber;
}

quint8 HbAuthStatusContract::maxTries() const {
    return mMaxTries;
}
