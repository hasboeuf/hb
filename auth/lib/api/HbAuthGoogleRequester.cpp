// Qt
#include <QtCore/QJsonObject>
// Hb
#include <network/HbWebServiceJob.h>
// Local
#include <HbAuthConstants.h>
#include <api/HbAuthGoogleRequester.h>

using namespace hb::tools;
using namespace hb::auth;

static GoogleObject GL_OBJECT;

HbAuthGoogleRequester::HbAuthGoogleRequester(QNetworkAccessManager* networkAccessManager, QObject* parent) :
        HbAuthRequester(networkAccessManager, parent) {
}

void HbAuthGoogleRequester::requestUser() {
    QUrl url("https://www.googleapis.com/oauth2/v1/userinfo");
    QVariantMap parameter = {{"alt", "json"}};
    auto job = request(url, parameter);
    connect(job, &HbWebServiceJob::finished, this, &HbAuthGoogleRequester::onRequestUserFinished);
}

void HbAuthGoogleRequester::onRequestUserFinished(const HbWebServiceResult& result) {
    HbAuthUser user;
    user.setSource(HbAuthObject::GOOGLE);

    auto root = result.jsonContent().object();

    if (result.networkError() != QNetworkReply::NoError) {
        user.setError(HbAuthUser::NETWORK, result.networkErrorString());
        auto errorObject = root.value(GL_OBJECT.error).toObject();
        if (!errorObject.isEmpty()) {
            user.setError(HbAuthUser::API,
                          QString::number(errorObject.value(GL_OBJECT.errorCode).toInt()) + " "
                              + errorObject.value(GL_OBJECT.errorMessage).toString());
        }
    }

    if (root.isEmpty()) {
        user.setError(HbAuthUser::PARSING, "Bad JSON");
    } else {
        user.setId(root.value(GL_OBJECT.id).toString());
        user.setFirstName(root.value(GL_OBJECT.firstName).toString());
        user.setLastName(root.value(GL_OBJECT.lastName).toString());
        user.setLink(root.value(GL_OBJECT.link).toString());
        user.setEmail(root.value(GL_OBJECT.email).toString());
        user.setGender(root.value(GL_OBJECT.gender).toString());
        user.setLocale(root.value(GL_OBJECT.locale).toString());
        user.setVerified(root.value(GL_OBJECT.verified).toBool());
        user.setPicture(root.value(GL_OBJECT.picture).toString());
    }

    emit userRequestFinished(user);
}
