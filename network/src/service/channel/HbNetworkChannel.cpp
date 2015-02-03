// Local
#include <service/channel/HbNetworkChannel.h>
#include <contract/HbNetworkContract.h>

using namespace hb::network;

HbNetworkChannel::HbNetworkChannel()
{
    mUuid = HbNetworkProtocol::SERVICE_CHANNEL_USER;
}

servuuid HbNetworkChannel::uuid() const
{
    return mUuid;
}
