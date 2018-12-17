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

    mFacebookClient = nullptr;
    mFacebookServer = nullptr;
    mGoogleClient = nullptr;
    mGoogleServer = nullptr;

    connect(ui_qpb_facebook_connect, &QPushButton::clicked, this, &LinkMainWindow::onFacebookConnectClicked);
    connect(ui_qpb_google_connect, &QPushButton::clicked, this, &LinkMainWindow::onGoogleConnectClicked);

    connect(
        &mFacebookRequester, &HbFacebookRequester::requestCompleted, this, &LinkMainWindow::onFacebookRequestCompleted);
    connect(&mGoogleRequester, &HbGoogleRequester::requestCompleted, this, &LinkMainWindow::onGoogleRequestCompleted);
}

LinkMainWindow::~LinkMainWindow() {
    if (mFacebookClient)
        delete mFacebookClient;
    if (mFacebookServer)
        delete mFacebookServer;
    if (mGoogleClient)
        delete mGoogleClient;
    if (mGoogleServer)
        delete mGoogleServer;
}

void LinkMainWindow::onFacebookConnectClicked() {
    mFacebookClient = new HbO2ClientFacebook();

    connect(mFacebookClient, &HbO2::linkSucceed, this, &LinkMainWindow::onFacebookClientLinkSucceed);

    mFacebookClient->config().setClientId(msClientId);
    mFacebookClient->config().setLocalPort(8080);
    mFacebookClient->config().addScope(FB_PERMISSION_EMAIL);
    mFacebookClient->config().addScope(FB_PERMISSION_FRIENDS);
    mFacebookClient->config().setBrowserControls(&mBrowserControls);

    mFacebookClient->link();
}

void LinkMainWindow::onGoogleConnectClicked() {
    mGoogleClient = new HbO2ClientGoogle();

    connect(mGoogleClient, &HbO2::linkSucceed, this, &LinkMainWindow::onGoogleClientLinkSucceed);

    mGoogleClient->config().setClientId(msClientId);
    mGoogleClient->config().setLocalPort(8080);
    mGoogleClient->config().addScope(GL_PERMISSION_EMAIL);
    mGoogleClient->config().addScope(GL_PERMISSION_PROFILE);
    mGoogleClient->config().setBrowserControls(&mBrowserControls);

    mGoogleClient->link();
}

void LinkMainWindow::onFacebookClientLinkSucceed() {
    if (sender() != mFacebookClient) {
        return;
    }

    qDebug() << "Client link succeed";

    mFacebookServer = new HbO2ServerFacebook();

    connect(mFacebookServer,
            &HbO2ServerFacebook::linkSucceed,
            this,
            &LinkMainWindow::onFacebookServerLinkSucceed,
            Qt::UniqueConnection);

    mFacebookServer->config().setClientId(mFacebookClient->config().clientId());
    mFacebookServer->config().setClientSecret(msClientSecret);
    mFacebookServer->setRedirectUri(mFacebookClient->redirectUri());
    mFacebookServer->setCode(mFacebookClient->code());
    mFacebookServer->addField(FB_USER_FIRST_NAME);
    mFacebookServer->addField(FB_USER_LAST_NAME);
    mFacebookServer->addField(FB_USER_LINK);
    mFacebookServer->addField(FB_USER_EMAIL);
    mFacebookServer->addField(FB_USER_GENDER);
    mFacebookServer->addField(FB_USER_LOCALE);
    mFacebookServer->addField(FB_USER_VERIFIED);
    mFacebookServer->addField(FB_USER_TIMEZONE);

    mFacebookClient->deleteLater();
    mFacebookClient = nullptr;

    mFacebookServer->link();
}

void LinkMainWindow::onFacebookServerLinkSucceed() {
    if (sender() != mFacebookServer) {
        return;
    }

    qDebug() << "Server link succeed. Request facebook user...";

    quint64 request_id = mFacebookRequester.requestUser(mFacebookServer);
    if (request_id > 0) {
        qDebug() << "Request id:" << request_id;
    } else {
        qDebug() << "Request user failed";
    }

    mFacebookServer->deleteLater();
    mFacebookServer = nullptr;
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
    if (sender() != mGoogleClient) {
        return;
    }

    qDebug() << "Client link succeed";

    mGoogleServer = new HbO2ServerGoogle();

    connect(mGoogleServer,
            &HbO2ServerGoogle::linkSucceed,
            this,
            &LinkMainWindow::onGoogleServerLinkSucceed,
            Qt::UniqueConnection);

    mGoogleServer->config().setClientId(mGoogleClient->config().clientId());
    mGoogleServer->config().setClientSecret(msClientSecret);
    mGoogleServer->setRedirectUri(mGoogleClient->redirectUri());
    mGoogleServer->setCode(mGoogleClient->code());

    mGoogleClient->deleteLater();
    mGoogleClient = nullptr;

    mGoogleServer->link();
}

void LinkMainWindow::onGoogleServerLinkSucceed() {
    if (sender() != mGoogleServer) {
        return;
    }

    qDebug() << "Server link succeed. Request google user...";

    quint64 request_id = mGoogleRequester.requestUser(mGoogleServer);
    if (request_id > 0) {
        qDebug() << "Request id:" << request_id;
    } else {
        qWarning() << "Request user failed";
    }

    mGoogleServer->deleteLater();
    mGoogleServer = nullptr;
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
