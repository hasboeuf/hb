// Local
#include <service/channel/HbNetworkChannel.h>
#include <contract/HbNetworkContract.h>

using namespace hb::network;

HbNetworkChannel::HbNetworkChannel()
{
    mId = HbNetworkProtocol::SERVICE_CHANNEL;
}

serviceuid HbNetworkChannel::id() const
{
    return mId;
}
