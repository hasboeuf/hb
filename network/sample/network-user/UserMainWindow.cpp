// Qt
#include <QtCore/QDebug>
#include <QtCore/QSharedPointer>
#include <QtCore/QSortFilterProxyModel>
#include <QtCore/QString>
#include <QtCore/QThread>
#include <QtGui/QCloseEvent>
#include <QtGui/QDesktopServices>
#include <QtGui/QStandardItemModel>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMessageBox>
// Hb
#include <HbClient.h>
#include <HbGlobal.h>
#include <contract/HbNetworkHeader.h>
#include <contract/HbNetworkProtocol.h>
#include <contract/auth/HbOAuthRequestContract.h>
#include <facebook/HbO2ClientFacebook.h>
// Local
#include <ChatMessageContract.h>
#include <ClientChatChannel.h>
#include <ClientSumChannel.h>
#include <RequestSumContract.h>
#include <UserMainWindow.h>

using namespace hb::tools;
using namespace hb::link;
using namespace hb::network;
using namespace hb::networkexample;

QString UserMainWindow::msClientId = "940633959281250"; // Fake value.

UserMainWindow::UserMainWindow(QWidget* parent) : QMainWindow(parent) {
    // Ui
    setupUi(this);
    ui_qsw_stack->setCurrentIndex(PAGE_WELCOME);

    setWindowTitle("User");

    HbO2ClientConfig facebook_config;
    facebook_config.setClientId(msClientId);
    facebook_config.setLocalPort(8080);

    HbO2ClientConfig google_config;
    google_config.setClientId(msClientId);
    google_config.setLocalPort(8080);

    HbGeneralClientConfig config;
    config.setAppName("hb-network-example");
    config.setProtocolVersion(1);
    config.auth().enableFacebookAuth(facebook_config);
    config.auth().enableGoogleAuth(google_config);
    config.presence().setKeepAliveInterval(30);

    mHbClient = new HbClient(config);

    mSumChannel = new ClientSumChannel();
    mChatChannel = new ClientChatChannel();

    connect(mSumChannel, &ClientSumChannel::computationReceived, this, &UserMainWindow::onComputationReceived);
    connect(mChatChannel, &ClientChatChannel::chatMessageReceived, this, &UserMainWindow::onChatMessageReceived);

    connect(ui_qpb_start, &QPushButton::clicked, this, &UserMainWindow::onStartClicked);
    connect(ui_qpb_stop, &QPushButton::clicked, this, &UserMainWindow::onStopClicked);
    connect(ui_qpb_fb_authentication, &QPushButton::clicked, this, &UserMainWindow::onFacebookAuthRequest);
    connect(ui_qpb_gl_authentication, &QPushButton::clicked, this, &UserMainWindow::onGoogleAuthRequest);
    connect(ui_qpb_unauthentication, &QPushButton::clicked, this, &UserMainWindow::onUnauthRequest);
    connect(ui_qpb_send, &QPushButton::clicked, this, &UserMainWindow::onSendClicked);
    connect(ui_qpb_compute, &QPushButton::clicked, this, &UserMainWindow::onComputeClicked);

    connect(mHbClient, &HbClient::clientStatusChanged, this, &UserMainWindow::onClientStatusChanged);
    connect(mHbClient, &HbClient::meStatusChanged, this, &UserMainWindow::onMeStatusChanged);
}

UserMainWindow::~UserMainWindow() {
}

void UserMainWindow::onStartClicked() {
    HbTcpClientConfig config;
    config.setAddress(QHostAddress::LocalHost);
    config.setPort(4000);
    config.setReconnectionDelay(0);
    config.setBadHeaderTolerant(false);

    config.plugChannel(mSumChannel);
    config.plugChannel(mChatChannel);

    networkuid client_uid = mHbClient->joinTcpClient(config, true);
    if (client_uid > 0) {
        qDebug() << "Client started" << client_uid;
    }
}

void UserMainWindow::onStopClicked() {
    mHbClient->leave();
}

void UserMainWindow::onSendClicked() {
    mChatChannel->sendMessage(ui_qle_chat->text());
    ui_qle_chat->clear();
}

void UserMainWindow::onComputeClicked() {
    mSumChannel->requestSum(ui_qsb_a->value(), ui_qsb_b->value());
}

void UserMainWindow::onFacebookAuthRequest() {
    mHbClient->OAuthRequested(HbAuthService::AUTH_FACEBOOK);
}

void UserMainWindow::onGoogleAuthRequest() {
    mHbClient->OAuthRequested(HbAuthService::AUTH_GOOGLE);
}

void UserMainWindow::onUnauthRequest() {
    qWarning() << "TODO";
}

void UserMainWindow::onClientStatusChanged(networkuid client_uid, HbNetworkProtocol::ClientStatus status) {
    qDebug() << "Status changed on client" << client_uid << HbNetworkProtocol::MetaClientStatus::toString(status);
}

void UserMainWindow::onMeStatusChanged(HbNetworkProtocol::UserStatus status, ShConstHbNetworkUserInfo me_info) {
    qDebug() << "My status changed:" << HbNetworkProtocol::MetaUserStatus::toString(status);

    if (status == HbNetworkProtocol::USER_DISCONNECTED) {
        ui_qsw_stack->setCurrentIndex(PAGE_WELCOME);
        ui_ql_me->clear();
    } else if (status == HbNetworkProtocol::USER_CONNECTING) {
    } else if (status == HbNetworkProtocol::USER_CONNECTED) {
        ui_qsw_stack->setCurrentIndex(PAGE_AUTH);
    } else if (status == HbNetworkProtocol::USER_AUTHENTICATING) {
    } else if (status == HbNetworkProtocol::USER_AUTHENTICATED) {
        resetGui();
        ui_qsw_stack->setCurrentIndex(PAGE_APP);
        ui_ql_me->setText(me_info->firstName() + " " + me_info->lastName() + " (" + me_info->email() + ")");
    }
}

void UserMainWindow::onChatUserJoined(ShConstHbNetworkUserInfo user_info) {
    ui_qte_chat->append(QString("%1 joined.").arg(user_info->nickname()));
}

void UserMainWindow::onChatUserLeft(ShConstHbNetworkUserInfo user_info) {
    ui_qte_chat->append(QString("%1 left.").arg(user_info->nickname()));
}

void UserMainWindow::onChatMessageReceived(const QString& author, const QString& message) {
    ui_qte_chat->append(QString("%1> %2").arg(author).arg(message));
}

void UserMainWindow::onComputationReceived(qint32 result) {
    ui_qsb_sum->setValue(result);
}

void UserMainWindow::resetGui() {
    ui_qle_chat->clear();
    ui_qte_chat->clear();
    ui_qsb_a->clear();
    ui_qsb_b->clear();
    ui_qsb_sum->clear();
}
