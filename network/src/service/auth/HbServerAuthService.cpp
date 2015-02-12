// Qt
// Hb
#include <facebook/HbO2ServerFacebook.h>
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
    mpStrategy = nullptr;
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
        if( auth_contract->type() == HbAuthRequestContract::AUTH_FACEOOK )
        {
            if ( !tryFacebookLogin( auth_contract ) )
            {
                HbError( "Something wrong occured." );
            }
        }
        else if( auth_contract->type() == HbAuthRequestContract::AUTH_USER )
        {
            if( mpStrategy )
            {
                mpStrategy->tryLogin( auth_contract );
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
}

void HbServerAuthService::onSocketConnected   ( sockuuid socket_uuid )
{

}

void HbServerAuthService::onSocketDisconnected( sockuuid socket_uuid )
{

}

bool HbServerAuthService::tryFacebookLogin( const HbAuthRequestContract * contract )
{
    const HbAuthFacebookRequestContract * facebook_auth =
            dynamic_cast< const HbAuthFacebookRequestContract * >( contract );

    if( !facebook_auth )
    {
        return false;
    }

    HbO2ServerFacebook * server_auth = new HbO2ServerFacebook();

    //connect( server_auth, &HbO2ServerFacebook::linkingSucceed, this, &HbServerAuthService::onFacebookLinkSucceed, Qt::UniqueConnection );
    // TODO how to retrieve contract? how to retrieve the sender?

    server_auth->setClientId    ( facebook_auth->client().clientId() );
    server_auth->setRedirectUri ( facebook_auth->client().redirectUri() );
    server_auth->setCode        ( facebook_auth->client().code() );
    server_auth->setClientSecret( "74621eedf9aa2cde9cd31dc5c4d3c440" );

    server_auth->link();

    return true;
}
