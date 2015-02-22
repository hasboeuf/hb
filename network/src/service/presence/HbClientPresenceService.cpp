// Qt
// Hb
// Local
#include <service/presence/HbClientPresenceService.h>

using namespace hb::network;

const HbServicePresenceClientConfig & HbClientPresenceService::config() const
{
    return mConfig;
}

void HbClientPresenceService::setConfig( const HbServicePresenceClientConfig & config )
{
    if( config.isValid() )
    {
        mConfig = config;
    }
}

void HbClientPresenceService::onUserConnected   ( const HbNetworkUserInfo & user_info )
{

}

void HbClientPresenceService::onUserDisconnected( const HbNetworkUserInfo & user_info )
{

}

void HbClientPresenceService::onContractReceived( const HbNetworkContract * contract )
{

}
