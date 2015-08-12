// Qt
// Hb
// Local
#include <user/HbNetworkUser.h>

using namespace hb::network;

HbNetworkUser::HbNetworkUser()
{
    reset();
}

void HbNetworkUser::reset()
{
    setStatus( HbNetworkProtocol::USER_DISCONNECTED );
    mMainSocketUid = 0;
    mInfo.clear();
    mInfo = ShConstHbNetworkUserInfo( new HbNetworkUserInfo() ); // Valid object instead of nullptr to avoid checking ptr everytime.
}

ShConstHbNetworkUserInfo & HbNetworkUser::info()
{
    return mInfo;
}

void HbNetworkUser::setInfo( const HbNetworkUserInfo & user_info )
{
    mInfo.clear();
    mInfo = ShConstHbNetworkUserInfo( new HbNetworkUserInfo( user_info ) );
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
    if( socket_uid == 0 )
    {
        mSocketsUid.remove( mMainSocketUid );
    }
    else
    {
        mSocketsUid.insert( socket_uid );
    }

    mMainSocketUid = socket_uid;
}

const QSet< networkuid > & HbNetworkUser::socketsUid() const
{
    return mSocketsUid;
}

const HbNetworkUserData HbNetworkUser::createData( networkuid socket_id )
{
    q_assert( mSocketsUid.contains( socket_id ) );

    HbNetworkUserData data;
    data.setSocketUid( socket_id );
    data.setInfo( mInfo );
    return data;
}
