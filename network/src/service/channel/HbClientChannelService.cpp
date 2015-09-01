// Qt
// Hb
#include <HbLogService.h>
// Local
#include <service/channel/HbClientChannelService.h>
#include <service/channel/HbClientChannel.h>
#include <service/channel/HbClientPeopledChannel.h>

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

bool HbClientChannelService::addChannel( HbNetworkChannel * channel )
{
    bool ok = false;

    if( dynamic_cast< HbClientChannel * >( channel ) )
    {
        ok = HbChannelService::addChannel( channel );

        if( ok )
        {
            HbClientPeopledChannel * peopled_channel = dynamic_cast< HbClientPeopledChannel * >( channel );
            if( peopled_channel )
            {
            }
        }
    }

    return ok;
}

HbClientChannel * HbClientChannelService::channel( serviceuid channel_uid )
{
    return dynamic_cast< HbClientChannel * >( HbChannelService::channel( channel_uid ) );
}

void HbClientChannelService::onUserContractReceived( const HbNetworkUserData & user_data, const HbNetworkContract * contract )
{
    q_assert_ptr( contract );

    serviceuid channel_uid = contract->header().service();

    HbClientChannel * channel = this->channel( channel_uid );
    if( !channel )
    {
        HbError( "Null channel %d.", channel_uid );
        delete contract;
        return;
    }

    channel->onUserContractReceived( user_data, contract );
}

void HbClientChannelService::onUserConnected( const HbNetworkUserData & user_data )
{
    Q_UNUSED( user_data )
}

void HbClientChannelService::onUserDisconnected( const HbNetworkUserData & user_data )
{
    Q_UNUSED( user_data )
}
