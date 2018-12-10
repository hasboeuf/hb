// Qt
// Local
#include <HbAuth2GoogleFlow.h>

using namespace hb::auth;

HbAuth2GoogleFlow::HbAuth2GoogleFlow(QNetworkAccessManager* networkAccessManager, QObject* parent) :
        HbAuth2Flow(networkAccessManager, parent) {
    setAuthorizationUrl(QUrl("https://accounts.google.com/o/oauth2/v2/auth"));
    setAccessTokenUrl(QUrl("https://www.googleapis.com/oauth2/v4/token"));
    setScopeSeparator(" ");
}
