// Qt
// Hb
// Local
#include <user/HbNetworkUserData.h>

using namespace hb::network;

HbNetworkUserData::HbNetworkUserData()
{
}

HbNetworkUserData::HbNetworkUserData( const HbNetworkUserData & source )
{
    if( &source != this )
    {
        mSocketUid = source.mSocketUid;
        mInfo      = source.mInfo;
    }
}

HbNetworkUserData & HbNetworkUserData::operator=( const HbNetworkUserData & source )
{
    if( &source != this )
    {
        mSocketUid = source.mSocketUid;
        mInfo      = source.mInfo;
    }
    return ( *this );
}

const HbNetworkUserInfo * HbNetworkUserData::info() const
{
    return mInfo.data();
}

void HbNetworkUserData::setInfo( ShConstHbNetworkUserInfo & info )
{
    mInfo = info;
}

networkuid HbNetworkUserData::socketUid() const
{
    return mSocketUid;
}

void HbNetworkUserData::setSocketUid( networkuid socket_uid )
{
    mSocketUid = socket_uid;
}
