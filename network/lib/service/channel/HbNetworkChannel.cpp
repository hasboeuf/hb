// Hb
#include <HbLogService.h>
// Local
#include <service/channel/HbNetworkChannel.h>
#include <contract/HbNetworkContract.h>

using namespace hb::network;


HbNetworkChannel::HbNetworkChannel()
{
    mNetworkUid = 0;
}

void HbNetworkChannel::internalReset( bool keep_uid )
{
    if( !keep_uid )
    {
        mNetworkUid = 0;
    }
}

void HbNetworkChannel::setNetworkUid( networkuid network_uid )
{
    if( mNetworkUid == 0 )
    {
        mNetworkUid = network_uid;
    }
    else
    {
        qWarning() << "Network uid already set";
    }
}

networkuid HbNetworkChannel::networkUid() const
{
    return mNetworkUid;
}
