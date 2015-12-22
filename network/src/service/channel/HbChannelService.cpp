// Qt
// Hb
#include <HbLogService.h>
// Local
#include <service/channel/HbChannelService.h>
#include <service/channel/HbNetworkChannel.h>
#include <contract/channel/HbUserSyncContract.h>

using namespace hb::network;

HbChannelService::HbChannelService()
{
}

void HbChannelService::reset()
{
    foreach( HbNetworkChannel * channel, mChannels )
    {
        channel->reset();
    }
}

void HbChannelService::plugContracts( HbNetworkExchanges & exchanges )
{
    exchanges.plug< HbUserSyncContract >();
}

serviceuid HbChannelService::uid() const
{
    return HbNetworkProtocol::SERVICE_CHANNEL;
}

bool HbChannelService::addChannel( HbNetworkChannel * channel )
{
    q_assert_ptr( channel );
    q_assert( channel->networkUid() != 0 );

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

            connect( channel, &HbNetworkService::contractToSend, this, &HbChannelService::onContractToSend );
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

void HbChannelService::onContractToSend( const HbNetworkContract * contract )
{
    q_assert_ptr( contract );
    emit contractToSend( contract );
}
