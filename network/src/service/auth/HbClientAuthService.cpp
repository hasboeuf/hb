// Qt
// Hb
// Local
#include <service/auth/HbClientAuthService.h>

using namespace hb::network;

const HbServiceAuthClientConfig & HbClientAuthService::config() const
{
    return mConfig;
}

void HbClientAuthService::setConfig( const HbServiceAuthClientConfig & config )
{
    if( config.isValid() )
    {
        mConfig = config;
    }
}

void HbClientAuthService::onContractReceived( const HbNetworkContract * contract )
{

}

void HbClientAuthService::onSocketConnected   ( networkuid socket_uid )
{

}

void HbClientAuthService::onSocketDisconnected( networkuid socket_uid )
{

}
