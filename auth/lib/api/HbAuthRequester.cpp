// Qt
#include <QtCore/QUrl>
#include <QtCore/QUrlQuery>
#include <QtNetwork/QNetworkAccessManager>
// Local
#include <HbAuthConstants.h>
#include <api/HbAuthRequester.h>

using namespace hb::tools;
using namespace hb::auth;

static AuthKeys AUTH_KEYS;

static QUrlQuery createQuery(const QVariantMap& parameters) {
    // TODO duplicated
    QUrlQuery query;
    for (auto it = parameters.begin(), end = parameters.end(); it != end; ++it)
        query.addQueryItem(it.key(), it.value().toString());
    return query;
}

HbAuthRequester::HbAuthRequester(QNetworkAccessManager* networkAccessManager, QObject* parent) :
        QObject(parent),
        mWebServiceController(networkAccessManager) {
}

void HbAuthRequester::setConfig(const HbAuth2FlowConfig& config) {
    mConfig = config;
}

HbWebServiceJob* HbAuthRequester::request(const QUrl& url, const QVariantMap& parameters) {
    QUrl requestUrl(url);
    auto params = parameters;
    params.insert(AUTH_KEYS.accessToken, mConfig.accessToken());

    requestUrl.setQuery(createQuery(params));

    return mWebServiceController.get(requestUrl);
}
