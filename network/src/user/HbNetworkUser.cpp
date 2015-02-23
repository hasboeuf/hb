// Qt
// Hb
// Local
#include <user/HbNetworkUser.h>

using namespace hb::network;

HbNetworkUser::HbNetworkUser()
{
    mStatus = HbNetworkProtocol::USER_DISCONNECTED;
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
