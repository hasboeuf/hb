// Qt
#include <QtCore/QUrl>
#include <QtCore/QUrlQuery>
#include <QtNetwork/QNetworkReply>
// Hb
#include <core/HbDictionaryHelper.h>
#include <facebook/HbO2ClientFacebook.h>
#include <facebook/HbO2ServerFacebook.h>
#include <facebook/api/HbFacebookUser.h>
#include <google/HbO2ClientGoogle.h>
#include <google/HbO2ServerGoogle.h>
#include <google/api/HbGoogleUser.h>
// Local
#include <LinkMainWindow.h>

using namespace hb::link;
using namespace hb::linkexample;

QString LinkMainWindow::msClientId = "940633959281250";                      // Fake value.
QString LinkMainWindow::msClientSecret = "74621eedf9aa2cde9cd31dc5c4d3c440"; // Fake value.

LinkMainWindow::LinkMainWindow(QWidget* parent) : QMainWindow(parent) {
    // Ui
    setupUi(this);
    setWindowTitle("Link");

    mpFacebookClient = nullptr;
    mpFacebookServer = nullptr;
    mpGoogleClient = nullptr;
    mpGoogleServer = nullptr;

    connect(ui_qpb_facebook_connect, &QPushButton::clicked, this, &LinkMainWindow::onFacebookConnectClicked);
    connect(ui_qpb_google_connect, &QPushButton::clicked, this, &LinkMainWindow::onGoogleConnectClicked);

    connect(
        &mFacebookRequester, &HbFacebookRequester::requestCompleted, this, &LinkMainWindow::onFacebookRequestCompleted);
    connect(&mGoogleRequester, &HbGoogleRequester::requestCompleted, this, &LinkMainWindow::onGoogleRequestCompleted);
}

LinkMainWindow::~LinkMainWindow() {
    if (mpFacebookClient)
        delete mpFacebookClient;
    if (mpFacebookServer)
        delete mpFacebookServer;
    if (mpGoogleClient)
        delete mpGoogleClient;
    if (mpGoogleServer)
        delete mpGoogleServer;
}

void LinkMainWindow::onFacebookConnectClicked() {
    mpFacebookClient = new HbO2ClientFacebook();

    connect(mpFacebookClient, &HbO2::linkSucceed, this, &LinkMainWindow::onFacebookClientLinkSucceed);

    mpFacebookClient->config().setClientId(msClientId);
    mpFacebookClient->config().setLocalPort(8080);
    mpFacebookClient->config().addScope(FB_PERMISSION_EMAIL);
    mpFacebookClient->config().addScope(FB_PERMISSION_FRIENDS);
    mpFacebookClient->config().setBrowserControls(&mBrowserControls);

    mpFacebookClient->link();
}

void LinkMainWindow::onGoogleConnectClicked() {
    mpGoogleClient = new HbO2ClientGoogle();

    connect(mpGoogleClient, &HbO2::linkSucceed, this, &LinkMainWindow::onGoogleClientLinkSucceed);

    mpGoogleClient->config().setClientId(msClientId);
    mpGoogleClient->config().setLocalPort(8080);
    mpGoogleClient->config().addScope(GL_PERMISSION_EMAIL);
    mpGoogleClient->config().addScope(GL_PERMISSION_PROFILE);
    mpGoogleClient->config().setBrowserControls(&mBrowserControls);

    mpGoogleClient->link();
}

void LinkMainWindow::onFacebookClientLinkSucceed() {
    if (sender() != mpFacebookClient) {
        return;
    }

    qDebug() << "Client link succeed";

    mpFacebookServer = new HbO2ServerFacebook();

    connect(mpFacebookServer,
            &HbO2ServerFacebook::linkSucceed,
            this,
            &LinkMainWindow::onFacebookServerLinkSucceed,
            Qt::UniqueConnection);

    mpFacebookServer->config().setClientId(mpFacebookClient->config().clientId());
    mpFacebookServer->config().setClientSecret(msClientSecret);
    mpFacebookServer->setRedirectUri(mpFacebookClient->redirectUri());
    mpFacebookServer->setCode(mpFacebookClient->code());
    mpFacebookServer->addField(FB_USER_FIRST_NAME);
    mpFacebookServer->addField(FB_USER_LAST_NAME);
    mpFacebookServer->addField(FB_USER_LINK);
    mpFacebookServer->addField(FB_USER_EMAIL);
    mpFacebookServer->addField(FB_USER_GENDER);
    mpFacebookServer->addField(FB_USER_LOCALE);
    mpFacebookServer->addField(FB_USER_VERIFIED);
    mpFacebookServer->addField(FB_USER_TIMEZONE);

    mpFacebookClient->deleteLater();
    mpFacebookClient = nullptr;

    mpFacebookServer->link();
}

void LinkMainWindow::onFacebookServerLinkSucceed() {
    if (sender() != mpFacebookServer) {
        return;
    }

    qDebug() << "Server link succeed. Request facebook user...";

    quint64 request_id = mFacebookRequester.requestUser(mpFacebookServer);
    if (request_id > 0) {
        qDebug() << "Request id:" << request_id;
    } else {
        qDebug() << "Request user failed";
    }

    mpFacebookServer->deleteLater();
    mpFacebookServer = nullptr;
}

void LinkMainWindow::onFacebookRequestCompleted(quint64 request_id, hb::link::HbFacebookObject* object) {
    qDebug() << "Request completed" << request_id;
    if (!object) {
        qWarning() << "Facebook object null";
        return;
    }

    qDebug() << "Facebook object of type" << HbFacebookObject::MetaObjectType::toString(object->type()) << "received";

    if (object->type() == HbFacebookObject::OBJECT_USER) {
        HbFacebookUser* user = dynamic_cast<HbFacebookUser*>(object);
        if (user) {
            qDebug() << "Facebook user informations:" << user->toString();
        } else {
            qWarning() << "Bad dynamic cast HbFacebookObject -> HbFacebookUser";
        }
    } else {
        qWarning() << "No displayable for this type";
    }

    delete object;
}

void LinkMainWindow::onGoogleClientLinkSucceed() {
    if (sender() != mpGoogleClient) {
        return;
    }

    qDebug() << "Client link succeed";

    mpGoogleServer = new HbO2ServerGoogle();

    connect(mpGoogleServer,
            &HbO2ServerGoogle::linkSucceed,
            this,
            &LinkMainWindow::onGoogleServerLinkSucceed,
            Qt::UniqueConnection);

    mpGoogleServer->config().setClientId(mpGoogleClient->config().clientId());
    mpGoogleServer->config().setClientSecret(msClientSecret);
    mpGoogleServer->setRedirectUri(mpGoogleClient->redirectUri());
    mpGoogleServer->setCode(mpGoogleClient->code());

    mpGoogleClient->deleteLater();
    mpGoogleClient = nullptr;

    mpGoogleServer->link();
}

void LinkMainWindow::onGoogleServerLinkSucceed() {
    if (sender() != mpGoogleServer) {
        return;
    }

    qDebug() << "Server link succeed. Request google user...";

    quint64 request_id = mGoogleRequester.requestUser(mpGoogleServer);
    if (request_id > 0) {
        qDebug() << "Request id:" << request_id;
    } else {
        qWarning() << "Request user failed";
    }

    mpGoogleServer->deleteLater();
    mpGoogleServer = nullptr;
}

void LinkMainWindow::onGoogleRequestCompleted(quint64 request_id, hb::link::HbGoogleObject* object) {
    qDebug() << "Request completed" << request_id;
    if (!object) {
        qWarning() << "Google object null";
        return;
    }

    qDebug() << "Google object of type" << HbGoogleObject::MetaObjectType::toString(object->type()) << "received";

    if (object->type() == HbGoogleObject::OBJECT_USER) {
        HbGoogleUser* user = dynamic_cast<HbGoogleUser*>(object);
        if (user) {
            qDebug() << "Google user informations:" << user->toString();
        } else {
            qWarning() << "Bad dynamic cast HbGoogleObject -> HbGoogleUser";
        }
    } else {
        qWarning() << "No displayable for this type";
    }

    delete object;
}
