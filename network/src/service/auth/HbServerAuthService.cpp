// Qt
// Hb
#include <HbLogService.h>
// Local
#include <service/auth/HbServerAuthService.h>
#include <service/auth/HbServerAuthStrategy.h>
#include <contract/auth/HbAuthRequestContract.h>
#include <contract/auth/HbAuthFacebookRequestContract.h>
#include <service/auth/HbServerAuthFacebookStrategy.h>

using namespace hb::network;

HbServerAuthService::HbServerAuthService()
{
    mUuid = HbNetworkProtocol::SERVICE_AUTH;

    HbServerAuthFacebookStrategy * fb_strategy = new HbServerAuthFacebookStrategy();
    mStrategies.insert( fb_strategy->type(), fb_strategy );

    foreach( HbServerAuthStrategy * strategy, mStrategies )
    {
        if( strategy )
        {
            connect( strategy, &HbServerAuthStrategy::loginFailed,
                     this,     &HbServerAuthService::onLoginFailed, Qt::UniqueConnection );
            connect( strategy, &HbServerAuthStrategy::loginSucceed,
                     this,     &HbServerAuthService::onLoginSucceed, Qt::UniqueConnection );
        }
    }
}

HbServerAuthService::~HbServerAuthService()
{
    qDeleteAll( mStrategies );
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

void HbServerAuthService::onLoginSucceed( sockuuid sender, const HbNetworkUserInfo & user_info )
{

}

void HbServerAuthService::onLoginFailed ( sockuuid sender, HbNetworkProtocol::AuthStatus, const QString & description )
{

}
