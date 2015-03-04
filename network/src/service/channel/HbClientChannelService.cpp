// Qt
// Hb
// Local
#include <service/channel/HbClientChannelService.h>

using namespace hb::network;

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

void HbClientChannelService::onContractReceived( const HbNetworkContract * contract )
{
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
