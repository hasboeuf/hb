// Qt
// Hb
#include <HbLogService.h>
// Local
#include <service/auth/HbAuthService.h>
#include <service/auth/HbClientAuthLoginObject.h>
#include <service/auth/HbClientAuthGoogleStrategy.h>
#include <google/HbO2ClientGoogle.h>
#include <contract/auth/HbOAuthRequestContract.h>

using namespace hb::network;
using namespace hb::link;

void HbClientAuthGoogleStrategy::setConfig( const HbO2ClientConfig & config )
{
    HbClientOAuthStrategy::setConfig( config );
    mConfig.addScope( GL_PERMISSION_EMAIL );
    mConfig.addScope( GL_PERMISSION_PROFILE );
}

void HbClientAuthGoogleStrategy::reset()
{
    HbClientOAuthStrategy::reset();
}

authstgy HbClientAuthGoogleStrategy::type() const
{
    return HbAuthService::AUTH_GOOGLE;
}

bool HbClientAuthGoogleStrategy::prepareAuthContract( HbClientAuthLoginObject * login_object )
{
    HbO2ClientGoogle * google_client = new HbO2ClientGoogle();

    connect( google_client, &HbO2::linkSucceed,
             this, &HbClientOAuthStrategy::onLinkSucceed );
    connect( google_client, &HbO2::linkFailed,
             this, &HbClientOAuthStrategy::onLinkFailed );

    google_client->config().setClientId ( mConfig.clientId()  );
    google_client->config().setLocalPort( mConfig.localPort() );
    google_client->config().setScopes   ( mConfig.scopes()     );
    google_client->config().setBrowserControls( mConfig.browserControls() );

    mPendingCodes.insert( google_client, login_object->socketUid() );

    google_client->link();

    return true;
}
