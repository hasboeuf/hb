// Qt
#include <QtCore/QJsonObject>
#include <QtCore/QMessageAuthenticationCode>
// Hb
#include <network/HbWebServiceJob.h>
// Local
#include <HbAuthConstants.h>
#include <api/HbAuthFacebookRequester.h>

using namespace hb::tools;
using namespace hb::auth;

static FacebookObject FB_OBJECT;
static FacebookScope FB_SCOPE;

static QString fieldsForScopes(QStringList scopes) {
    QString fields = "first_name,last_name,middle_name,name,name_format,picture,short_name";
    for (const QString& scope : scopes) {
        fields += "," + scope;
    }
    return fields;
}

HbAuthFacebookRequester::HbAuthFacebookRequester(QNetworkAccessManager* networkAccessManager, QObject* parent) :
        HbAuthRequester(networkAccessManager, parent) {
}

void HbAuthFacebookRequester::requestUser() {
    QUrl url("https://graph.facebook.com/me");

    QMessageAuthenticationCode proof(QCryptographicHash::Sha256);
    proof.setKey(mConfig.clientSecret().toUtf8());
    proof.addData(mConfig.accessToken().toUtf8());

    QVariantMap parameter = {{FB_OBJECT.proof, proof.result().toHex()},
                             {FB_OBJECT.field, fieldsForScopes(mConfig.scopes())}};
    auto job = request(url, parameter);
    connect(job, &HbWebServiceJob::finished, this, &HbAuthFacebookRequester::onRequestUserFinished);
}

void HbAuthFacebookRequester::onRequestUserFinished(const HbWebServiceResult& result) {
    HbAuthUser user;
    user.setSource(HbAuthObject::FACEBOOK);

    auto root = result.jsonContent().object();

    if (result.networkError() != QNetworkReply::NoError) {
        user.setError(HbAuthUser::NETWORK, result.networkErrorString());
        auto errorObject = root.value(FB_OBJECT.error).toObject();
        if (!errorObject.isEmpty()) {
            user.setError(HbAuthUser::API,
                          QString::number(errorObject.value(FB_OBJECT.errorCode).toInt()) + " "
                              + errorObject.value(FB_OBJECT.errorMessage).toString());
        }
    }

    if (root.isEmpty()) {
        user.setError(HbAuthUser::PARSING, "Bad JSON");
    } else {
        user.setId(root.value(FB_OBJECT.id).toString());
        user.setFirstName(root.value(FB_OBJECT.firstName).toString());
        user.setLastName(root.value(FB_OBJECT.lastName).toString());
        user.setLink(root.value(FB_OBJECT.link).toString());
        user.setEmail(root.value(FB_OBJECT.email).toString());
        user.setGender(root.value(FB_OBJECT.gender).toString());
        user.setLocale(root.value(FB_OBJECT.locale).toString());
        user.setVerified(root.value(FB_OBJECT.verified).toBool());
        user.setTimezone(root.value(FB_OBJECT.timezone).toInt());
    }

    emit userRequestFinished(user);
}
