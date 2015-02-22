// Qt
// Hb
// Local
#include <service/presence/HbServerPresenceService.h>

using namespace hb::network;

const HbServicePresenceServerConfig & HbServerPresenceService::config() const
{
    return mConfig;
}

void HbServerPresenceService::setConfig( const HbServicePresenceServerConfig & config )
{
    if( config.isValid() )
    {
        mConfig = config;
    }
}

void HbServerPresenceService::onUserConnected   ( const HbNetworkUserInfo & user_info )
{

}

void HbServerPresenceService::onUserDisconnected( const HbNetworkUserInfo & user_info )
{

}

void HbServerPresenceService::onContractReceived( const HbNetworkContract * contract )
{

}
