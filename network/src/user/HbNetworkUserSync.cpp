// Qt
// Hb
#include <HbLogService.h>
// Local
#include <user/HbNetworkUserSync.h>

using namespace hb::network;

HbNetworkUserSync::HbNetworkUserSync()
{
    mStatus   = HbNetworkProtocol::NETWORK_USER_UNDEFINED;
}

void HbNetworkUserSync::setUserInfo( ShConstHbNetworkUserInfo user_info )
{
    if( !user_info.isNull() )
    {
        mUserInfo = *user_info.data();
    }
    else
    {
        HbError( "Null user information." );
    }
}

const HbNetworkUserInfo & HbNetworkUserSync::userInfo() const
{
    return mUserInfo;
}

void HbNetworkUserSync::setStatus( HbNetworkProtocol::NetworkUserStatus status )
{
    mStatus = status;
}

HbNetworkProtocol::NetworkUserStatus HbNetworkUserSync::status() const
{
    return mStatus;
}

namespace hb
{
    namespace network
    {
        QDataStream & operator<<( QDataStream & stream, const HbNetworkUserSync & user_sync )
        {
            stream << ( netwint ) user_sync.mStatus;
            stream << user_sync.mUserInfo;

            return stream;
        }

        QDataStream & operator>>( QDataStream & stream, HbNetworkUserSync & user_sync )
        {
            netwint status;
            stream >> status;
            stream >> user_sync.mUserInfo;

            user_sync.mStatus = ( HbNetworkProtocol::NetworkUserStatus ) status;

            return stream;
        }
    }
}
