// Qt
// Hb
#include <HbLogService.h>
// Local
#include <service/channel/HbChannelService.h>
#include <service/channel/HbNetworkChannel.h>

using namespace hb::network;

HbChannelService::HbChannelService()
{
}

HbNetworkProtocol::NetworkTypes HbChannelService::enabledNetworkTypes() const
{
    return HbNetworkProtocol::NETWORK_TCP |
           HbNetworkProtocol::NETWORK_WEB |
           HbNetworkProtocol::NETWORK_SSL |
           HbNetworkProtocol::NETWORK_UDP |
           HbNetworkProtocol::NETWORK_LOCAL |
           HbNetworkProtocol::NETWORK_BLUETOOTH;
}

serviceuid HbChannelService::uid() const
{
    return HbNetworkProtocol::SERVICE_CHANNEL;
}

bool HbChannelService::addChannel( HbNetworkChannel * channel )
{
    q_assert_ptr( channel );

    serviceuid channel_uid = channel->uid();
    bool ok = false;

    if( !mChannels.contains( channel_uid ) )
    {
        if( channel_uid < HbNetworkProtocol::SERVICE_USER )
        {
            HbError( "Bad range channel uid: %d must be >= %d", channel_uid, HbNetworkProtocol::SERVICE_USER );
        }
        else
        {
            mChannels.insert( channel_uid, channel );
            ok = true;
        }
    }
    else
    {
        HbError( "Channel %d already exists.", channel->uid() );
    }

    return ok;
}

HbNetworkChannel * HbChannelService::channel( serviceuid channel_uid )
{
    return mChannels.value( channel_uid, nullptr );
}
