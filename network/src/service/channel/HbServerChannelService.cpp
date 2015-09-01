// Qt
// Hb
#include <HbLogService.h>
// Local
#include <service/channel/HbServerChannelService.h>
#include <service/channel/HbServerChannel.h>
#include <service/channel/HbServerPeopledChannel.h>

using namespace hb::network;

void HbServerChannelService::reset()
{
    foreach( HbServerChannel * channel, mChannels )
    {
        channel->reset();
    }
}

void HbServerChannelService::plugContracts( HbNetworkExchanges & exchanges )
{
    Q_UNUSED( exchanges )
}

const HbServiceChannelServerConfig & HbServerChannelService::config() const
{
    return mConfig;
}

void HbServerChannelService::setConfig( const HbServiceChannelServerConfig & config )
{
    if( config.isValid() )
    {
        mConfig = config;
    }
}

bool HbServerChannelService::addChannel( HbNetworkChannel * channel )
{

    bool ok = false;

    if( dynamic_cast< HbServerChannel * >( channel ) )
    {
        ok = HbChannelService::addChannel( channel );

        if( ok )
        {
            HbServerPeopledChannel * peopled_channel = dynamic_cast< HbServerPeopledChannel * >( channel );
            if( peopled_channel )
            {
            }
        }
    }

    return ok;
}

HbServerChannel * HbServerChannelService::channel( serviceuid channel_uid )
{
    return dynamic_cast< HbServerChannel * >( HbChannelService::channel( channel_uid ) );
}

void HbServerChannelService::onUserContractReceived( const HbNetworkUserData & user_data, const HbNetworkContract * contract )
{
    q_assert_ptr( contract );

    serviceuid channel_uid = contract->header().service();

    HbServerChannel * channel = this->channel( channel_uid );
    if( !channel )
    {
        HbError( "Null channel %d.", channel_uid );
        // TODO Kick user
        delete contract;
        return;
    }

    channel->onUserContractReceived( user_data, contract );
}

void HbServerChannelService::onUserConnected( const HbNetworkUserData & user_data )
{
    Q_UNUSED( user_data )
}

void HbServerChannelService::onUserDisconnected( const HbNetworkUserData & user_data )
{
    Q_UNUSED( user_data )
}
