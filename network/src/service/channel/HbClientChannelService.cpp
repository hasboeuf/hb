// Qt
// Hb
// Local
#include <service/channel/HbClientChannelService.h>
#include <service/channel/HbClientChannel.h>

using namespace hb::network;

void HbClientChannelService::reset()
{
    foreach( HbClientChannel * channel, mChannels )
    {
        channel->reset();
    }
}

void HbClientChannelService::plugContracts( HbNetworkExchanges & exchanges )
{
    Q_UNUSED( exchanges )
}

const HbServiceChannelClientConfig & HbClientChannelService::config() const
{
    return mConfig;
}

void HbClientChannelService::setConfig( const HbServiceChannelClientConfig & config )
{
    if( config.isValid() )
    {
        mConfig = config;
    }
}

void HbClientChannelService::onUserContractReceived( const HbNetworkUserInfo & user_info, const HbNetworkContract * contract )
{
    Q_UNUSED( user_info )
    Q_UNUSED( contract )
}

void HbClientChannelService::onUserConnected   ( const HbNetworkUserInfo & user_info )
{
    Q_UNUSED( user_info )
}

void HbClientChannelService::onUserDisconnected( const HbNetworkUserInfo & user_info )
{
    Q_UNUSED( user_info )
}
