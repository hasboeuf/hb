// Qt
// Hb
#include <HbLogService.h>
#include <facebook/HbO2ClientFacebook.h>
// Local
#include <service/auth/HbClientAuthService.h>
#include <contract/auth/HbAuthFacebookRequestContract.h>

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

void HbClientAuthService::onAuthRequest( networkuid socket_id, hb::link::HbO2ClientFacebook * facebook_client )
{
    q_assert_ptr( facebook_client );

    if( facebook_client->linkStatus() != HbO2ClientFacebook::LINKED )
    {
        HbError( "Facebook client not linked." );
        emit userUnauthenticated( socket_id, "Unlinked Facebook connection." );
        return;
    }

    mPendingSocket.insert( socket_id );

    HbAuthFacebookRequestContract * request_contract = new HbAuthFacebookRequestContract();
    request_contract->setClient( *facebook_client );
    // TODO request_contract->setType();

    // emit contractSent TODO
}
