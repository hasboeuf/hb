// Hb
#include <HbLogService.h>
#include <google/HbO2ServerGoogle.h>
#include <google/api/HbGoogleUser.h>
// Local
#include <contract/auth/HbOAuthRequestContract.h>
#include <service/auth/HbAuthService.h>
#include <service/auth/HbServerAuthGoogleStrategy.h>
#ifdef DEV
#include <mock/HbNetworkUserInfoMock.h>
#endif

using namespace hb::network;
using namespace hb::link;

HbServerAuthGoogleStrategy::HbServerAuthGoogleStrategy() : HbServerOAuthStrategy() {
    connect(&mRequester,
            &HbGoogleRequester::requestCompleted,
            this,
            &HbServerAuthGoogleStrategy::onRequestCompleted,
            Qt::UniqueConnection);
}

authstgy HbServerAuthGoogleStrategy::type() const {
    return HbAuthService::AUTH_GOOGLE;
}

bool HbServerAuthGoogleStrategy::checkLogin(const HbAuthRequestContract* contract) {
    const HbOAuthRequestContract* google_auth = contract->value<HbOAuthRequestContract>();

    if (!google_auth) {
        return false;
    }

    HbO2ServerGoogle* server_auth = new HbO2ServerGoogle();

    connect(server_auth,
            &HbO2ServerGoogle::linkSucceed,
            this,
            &HbServerAuthGoogleStrategy::onLinkSucceed,
            Qt::UniqueConnection);
    connect(
        server_auth, &HbO2ServerGoogle::linkFailed, this, &HbServerOAuthStrategy::onLinkFailed, Qt::UniqueConnection);

    server_auth->config().setClientId(mConfig.clientId());
    server_auth->config().setClientSecret(mConfig.clientSecret());
    server_auth->setRedirectUri(google_auth->redirectUri());
    server_auth->setCode(google_auth->code());

    mPendingToken.insert(server_auth, contract->sender());

    server_auth->link();

    return true;
}

// Problem: onLinkSucceed and onLinkFailed are both called. That causes problems
// as deleterLater is called in each of them.

void HbServerAuthGoogleStrategy::onLinkSucceed() {
    HbO2ServerGoogle* server_auth = dynamic_cast<HbO2ServerGoogle*>(sender());
    q_assert_ptr(server_auth);
    q_assert(mPendingToken.contains(server_auth));

    qDebug() << "Server link succeed. Requesting Google user object" << server_auth->config().clientId();

    networkuid sender = mPendingToken.take(server_auth);
    quint64 request_id = mRequester.requestUser(server_auth);
    if (request_id > 0) {
        mPendingRequest.insert(request_id, sender);
    } else {
        emit authFailed(sender, HbNetworkProtocol::AUTH_INTERNAL_ERROR, "");
    }

    server_auth->deleteLater();
}

void HbServerAuthGoogleStrategy::onRequestCompleted(quint64 request_id, HbGoogleObject* object) {
    q_assert(mPendingRequest.contains(request_id));

    networkuid sender = mPendingRequest.take(request_id);

    HbGoogleUser* user = dynamic_cast<HbGoogleUser*>(object);
    if (user) {
        qDebug() << "Google user informations:" << user->toString();

        HbNetworkUserInfo user_info;
        user_info.setId(user->id());
        user_info.setType(HbAuthService::AUTH_FACEBOOK);
        user_info.setEmail(user->email());
        user_info.setNickname(user->firstName() + " " + user->lastName());
        user_info.setFirstName(user->firstName());
        user_info.setLastName(user->lastName());
        if (user->gender() == "male") {
            user_info.setGender(HbNetworkUserInfo::GENDER_MALE);
        } else if (user->gender() == "female") {
            user_info.setGender(HbNetworkUserInfo::GENDER_FEMALE);
        }
        user_info.setPicture(user->picture());

#ifdef DEV
        HbNetworkUserInfoMock::mockNetworkUserInfo(user_info); // Randomize user.
#endif

        emit authSucceed(sender, user_info);
    } else {
        qWarning() << "Bad dynamic cast HbGoogleObject -> HbGoogleUser";
        emit authFailed(sender, HbNetworkProtocol::AUTH_OAUTH_KO, "");
    }

    if (object) {
        delete object;
    }
}
