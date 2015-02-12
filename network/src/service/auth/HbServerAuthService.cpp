// Qt
// Hb
#include <HbLogService.h>
// Local
#include <service/auth/HbServerAuthService.h>
#include <service/auth/HbServerAuthStrategy.h>
#include <contract/auth/HbAuthRequestContract.h>
#include <contract/auth/HbAuthFacebookRequestContract.h>

using namespace hb::network;

HbServerAuthService::HbServerAuthService()
{
    mUuid = HbNetworkProtocol::SERVICE_AUTH;
}

HbNetworkProtocol::NetworkTypes HbServerAuthService::enabledNetworkTypes() const
{
    return HbNetworkProtocol::NETWORK_TCP |
           HbNetworkProtocol::NETWORK_SSL;
}

void HbServerAuthService::onContractReceived( const HbNetworkContract * contract )
{
    const HbAuthRequestContract * auth_contract = contract->value< const HbAuthRequestContract >();
    if( auth_contract )
    {
        authstgy type = auth_contract->type();

        HbServerAuthStrategy * strategy = mStrategies.value( type, nullptr );
        if( strategy )
        {
            strategy->tryLogin( auth_contract );
        }
        else
        {
            HbError( "No user auth strategy defined." );
            // TODO kick?
        }
    }
    else
    {
        HbError( "Auth contract type not recognized." );
        // TODO kick?
    }
}

void HbServerAuthService::onSocketConnected   ( sockuuid socket_uuid )
{

}

void HbServerAuthService::onSocketDisconnected( sockuuid socket_uuid )
{

}
