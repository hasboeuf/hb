// Qt
// Hb
// Local
#include <service/channel/HbServerChannelService.h>

using namespace hb::network;

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

void HbServerChannelService::onContractReceived( const HbNetworkContract * contract )
{
    Q_UNUSED( contract )
}

void HbServerChannelService::onUserConnected   ( const HbNetworkUserInfo & user_info )
{
    Q_UNUSED( user_info )
}

void HbServerChannelService::onUserDisconnected( const HbNetworkUserInfo & user_info )
{
    Q_UNUSED( user_info )
}
