// Local
#include <service/channel/HbNetworkChannel.h>
#include <contract/HbNetworkContract.h>

using namespace hb::network;

HbNetworkChannel::HbNetworkChannel()
{
    mId = HbNetworkProtocol::SERVICE_CHANNEL_USER;
}

servuid HbNetworkChannel::id() const
{
    return mId;
}
