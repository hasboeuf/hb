// Qt
// Hb
// Local
#include <user/HbNetworkUser.h>

using namespace hb::network;

HbNetworkUser::HbNetworkUser()
{
    mStatus = HbNetworkProtocol::USER_DISCONNECTED;
    mSocketUid = 0;
}

const HbNetworkUserInfo & HbNetworkUser::info() const
{
    return mInfo;
}

void HbNetworkUser::setInfo( const HbNetworkUserInfo & info )
{
    mInfo = info;
}

HbNetworkProtocol::UserStatus HbNetworkUser::status() const
{
    return mStatus;
}

void HbNetworkUser::setStatus( HbNetworkProtocol::UserStatus status )
{
    mStatus = status;
    emit statusChanged( status );
}

networkuid HbNetworkUser::socketUid() const
{
    return mSocketUid;
}

void HbNetworkUser::setSocketUid( networkuid socket_uid )
{
    mSocketUid = socket_uid;
}
