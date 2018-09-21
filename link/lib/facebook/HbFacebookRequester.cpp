// Qt
#include <QtCore/QJsonObject>
#include <QtCore/QUrl>
#include <QtCore/QUrlQuery>
// Hb
#include <HbLogService.h>
#include <core/HbDictionaryHelper.h>
// Local
#include <facebook/HbFacebookRequester.h>
#include <facebook/HbO2ServerFacebook.h>
#include <facebook/api/HbFacebookUser.h>

using namespace hb::link;

HbFacebookRequester::HbFacebookRequester() : HbHttpRequester() {
    connect(
        this, &HbHttpRequester::requestFinished, this, &HbFacebookRequester::onRequestFinished, Qt::UniqueConnection);
    connect(this, &HbHttpRequester::requestError, this, &HbFacebookRequester::onRequestError, Qt::UniqueConnection);
}

quint64 HbFacebookRequester::requestUser(HbO2ServerFacebook* auth) {
    if (!auth || (auth->linkStatus() != HbO2::LINKED)) {
        qWarning() << "Auth null or unlinked";
        return false;
    }

    QUrl url("https://graph.facebook.com/me");
    QUrlQuery request(url);

    QHash<QString, QString> params;
    params.insert(OAUTH2_ACCESS_TOKEN, auth->token());
    params.insert(FB_EXTRA_FIELDS, auth->fields()); // Since Facebook graph 2.4.

    request.setQueryItems(HbDictionaryHelper::toPairList<QString, QString>(params));
    url.setQuery(request);

    quint64 id = processRequest(url);
    if (id > 0) {
        mRequestTypes.insert(id, HbFacebookObject::OBJECT_USER);
        qWarning() << "Request" << id << "is sent" << url.toString();
    }

    return id;
}

void HbFacebookRequester::onRequestFinished(quint64 request_id, const QJsonDocument& doc) {
    HbFacebookObject::ObjectType type = HbFacebookObject::OBJECT_NONE;

    if (mRequestTypes.contains(request_id)) {
        type = mRequestTypes.take(request_id);
    }

    qDebug() << "Request" << request_id << "of type" << HbFacebookObject::MetaObjectType::toString(type) << "completed";

    if (type == HbFacebookObject::OBJECT_USER) {
        HbFacebookUser* user = new HbFacebookUser();
        user->load(doc);
        emit requestCompleted(request_id, user);
    } else {
        qWarning() << "Object creation failed, bad type";
        emit requestCompleted(request_id, nullptr);
    }
}

void HbFacebookRequester::onRequestError(quint64 request_id, const QString& error) {
    HbFacebookObject::ObjectType type = HbFacebookObject::OBJECT_NONE;

    if (mRequestTypes.contains(request_id)) {
        type = mRequestTypes.take(request_id);
    }

    qWarning() << "Request" << request_id << "of type" << HbFacebookObject::MetaObjectType::toString(type) << "failed"
               << error;

    emit requestCompleted(request_id, nullptr);
}
