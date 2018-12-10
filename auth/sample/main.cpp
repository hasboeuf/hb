// Qt
#include <QtCore/QCommandLineParser>
#include <QtCore/QDebug>
#include <QtCore/QEventLoop>
#include <QtCore/QTimer>
#include <QtGui/QDesktopServices>
#include <QtNetwork/QNetworkAccessManager>
#include <QtWidgets/QApplication>
// Hb
#include <HbAuth.h>
#include <HbLogService.h>
#include <api/HbAuthFacebookRequester.h>
#include <api/HbAuthGoogleRequester.h>
#include <core/HbApplicationHelper.h>
// Local
#include <HbAuth2FacebookFlow.h>
#include <HbAuth2GoogleFlow.h>
#include <HbAuthConstants.h>

using namespace hb::auth;

static constexpr char FACEBOOK_ID_OPT[] = "fbid";
static constexpr char FACEBOOK_SECRET_OPT[] = "fbsecret";
static constexpr char GOOGLE_ID_OPT[] = "glid";
static constexpr char GOOGLE_SECRET_OPT[] = "glsecret";

static const FacebookScope FB_SCOPE;
static const GoogleScope GL_SCOPE;

static void waitForStatus(HbAuth2Flow* flow, HbAuth2Flow::Status expectedStatus) {
    QEventLoop loop;
    QObject::connect(flow, &HbAuth2Flow::statusChanged, [&loop, expectedStatus](HbAuth2Flow::Status status) {
        if (status == expectedStatus) {
            loop.quit();
        }
    });
    loop.exec();
}

static void printResult(HbAuth2Flow* flow) {
    qDebug().nospace() << "code: " << flow->authorizationCode() << "\n"
                       << "access_token: " << flow->accessToken();
}

static void openUrl(const QUrl& url) {
    QDesktopServices::openUrl(url);
}

void runWholeFlow(HbAuth2Flow* flow, const HbAuth2FlowConfig& config) {
    QObject::connect(flow, &HbAuth2Flow::authorizeWithBrowser, &openUrl);
    flow->init(config);
    flow->requestAuthorizationCode();
    waitForStatus(flow, HbAuth2Flow::Status::TemporaryCredentialsReceived);
    flow->requestAccessToken();
    waitForStatus(flow, HbAuth2Flow::Status::Granted);
    printResult(flow);
}

QString runClientFlow(HbAuth2Flow* flow, const HbAuth2FlowConfig& config) {
    QObject::connect(flow, &HbAuth2Flow::authorizeWithBrowser, &openUrl);
    flow->init(config);
    flow->requestAuthorizationCode();
    waitForStatus(flow, HbAuth2Flow::Status::TemporaryCredentialsReceived);
    printResult(flow);
    return flow->authorizationCode();
}

void runServerFlow(HbAuth2Flow* flow, const HbAuth2FlowConfig& config) {
    flow->init(config);
    flow->requestAccessToken();
    waitForStatus(flow, HbAuth2Flow::Status::Granted);
    printResult(flow);
}

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    hb::auth::init();

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addOption(QCommandLineOption(FACEBOOK_ID_OPT, "facebook_id", "facebook_id"));
    parser.addOption(QCommandLineOption(FACEBOOK_SECRET_OPT, "facebook_secret", "facebook_secret"));
    parser.addOption(QCommandLineOption(GOOGLE_ID_OPT, "google_id", "google_id"));
    parser.addOption(QCommandLineOption(GOOGLE_SECRET_OPT, "google_secret", "google_secret"));
    parser.process(a.arguments());

    QNetworkAccessManager nam;

    QTimer::singleShot(0, [&parser, &nam]() {
        if (parser.isSet(FACEBOOK_ID_OPT) && parser.isSet(FACEBOOK_SECRET_OPT)) {
            HbAuth2FlowConfig config;
            config.setClientId(parser.value(FACEBOOK_ID_OPT));
            config.setClientSecret(parser.value(FACEBOOK_SECRET_OPT));
            config.setRedirectUrl(QUrl("https://localhost:8989/"));
            config.addScope(FB_SCOPE.email);

            HbAuth2Flow* wholeflow = new HbAuth2FacebookFlow(&nam);
            runWholeFlow(wholeflow, config);
            delete wholeflow;

            HbAuth2Flow* clientFlow = new HbAuth2FacebookFlow(&nam);
            runClientFlow(clientFlow, config);
            config = clientFlow->config();
            delete clientFlow;

            HbAuth2Flow* serverFlow = new HbAuth2FacebookFlow(&nam);
            runServerFlow(serverFlow, config);
            config = serverFlow->config();
            delete serverFlow;

            HbAuthFacebookRequester* requester = new HbAuthFacebookRequester(&nam);
            requester->setConfig(config);
            requester->requestUser();

            QObject::connect(
                requester, &HbAuthRequester::userRequestFinished, requester, [requester](const HbAuthUser& user) {
                    qDebug().noquote() << "user received:\n" << user.toString();
                    requester->deleteLater();
                });
        }

        if (parser.isSet(GOOGLE_ID_OPT) && parser.isSet(GOOGLE_SECRET_OPT)) {
            HbAuth2FlowConfig config;
            config.setClientId(parser.value(GOOGLE_ID_OPT));
            config.setClientSecret(parser.value(GOOGLE_SECRET_OPT));
            config.setRedirectUrl(QUrl("http://localhost:8989"));
            config.addScope(GL_SCOPE.email);
            config.addScope(GL_SCOPE.profile);

            HbAuth2Flow* wholeflow = new HbAuth2GoogleFlow(&nam);
            runWholeFlow(wholeflow, config);
            delete wholeflow;

            HbAuth2Flow* clientFlow = new HbAuth2GoogleFlow(&nam);
            runClientFlow(clientFlow, config);
            config = clientFlow->config();
            delete clientFlow;

            HbAuth2Flow* serverFlow = new HbAuth2GoogleFlow(&nam);
            runServerFlow(serverFlow, config);
            config = serverFlow->config();
            delete serverFlow;

            HbAuthGoogleRequester* requester = new HbAuthGoogleRequester(&nam);
            requester->setConfig(config);
            requester->requestUser();

            QObject::connect(
                requester, &HbAuthRequester::userRequestFinished, requester, [requester](const HbAuthUser& user) {
                    qDebug().noquote() << "user received:\n" << user.toString();
                    requester->deleteLater();
                });
        }
    });

    return a.exec();
}
