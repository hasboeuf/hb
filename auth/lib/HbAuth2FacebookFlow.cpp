// Qt
// Local
#include <HbAuth2FacebookFlow.h>

using namespace hb::auth;

HbAuth2FacebookFlow::HbAuth2FacebookFlow(QNetworkAccessManager* networkAccessManager, QObject* parent) :
        HbAuth2Flow(networkAccessManager, parent) {
    setAuthorizationUrl(QUrl("https://www.facebook.com/dialog/oauth"));
    setAccessTokenUrl(QUrl("https://graph.facebook.com/oauth/access_token"));
}
