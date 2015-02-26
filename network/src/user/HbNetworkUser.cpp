// Qt
// Hb
// Local
#include <user/HbNetworkUser.h>

using namespace hb::network;

HbNetworkUser::HbNetworkUser()
{
    mStatus = HbNetworkProtocol::USER_DISCONNECTED;
    mMainSocketUid = 0;
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

networkuid HbNetworkUser::mainSocketUid() const
{
    return mMainSocketUid;
}

void HbNetworkUser::setMainSocketUid( networkuid socket_uid )
{
    if( socket_uid > 0 )
    {
        mMainSocketUid = socket_uid;
        mSocketsUid.insert( socket_uid );
    }
}

const QSet< networkuid > & HbNetworkUser::socketsUid() const
{
    return mSocketsUid;
}
