// Qt
// Hb
#include <HbLogService.h>
#include <facebook/HbO2ServerFacebook.h>
#include <facebook/api/HbFacebookUser.h>
// Local
#include <contract/auth/HbOAuthRequestContract.h>
#include <service/auth/HbAuthService.h>
#include <service/auth/HbClientAuthFacebookStrategy.h>
#include <service/auth/HbClientAuthLoginObject.h>

using namespace hb::network;
using namespace hb::link;

void HbClientAuthFacebookStrategy::setConfig(const HbO2ClientConfig& config) {
    HbClientOAuthStrategy::setConfig(config);
    mConfig.addScope(FB_PERMISSION_EMAIL);
}

void HbClientAuthFacebookStrategy::reset() {
    HbClientOAuthStrategy::reset();
}

authstgy HbClientAuthFacebookStrategy::type() const {
    return HbAuthService::AUTH_FACEBOOK;
}

bool HbClientAuthFacebookStrategy::prepareAuthContract(HbClientAuthLoginObject* login_object) {
    HbO2ClientFacebook* facebook_client = new HbO2ClientFacebook();

    connect(facebook_client, &HbO2::linkSucceed, this, &HbClientOAuthStrategy::onLinkSucceed);
    connect(facebook_client, &HbO2::linkFailed, this, &HbClientOAuthStrategy::onLinkFailed);

    facebook_client->config().setClientId(mConfig.clientId());
    facebook_client->config().setLocalPort(mConfig.localPort());
    facebook_client->config().setScopes(mConfig.scopes());
    facebook_client->config().setBrowserControls(mConfig.browserControls());

    mPendingCodes.insert(facebook_client, login_object->socketUid());

    facebook_client->link();

    return true;
}
