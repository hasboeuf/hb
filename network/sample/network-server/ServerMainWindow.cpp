// Qt
#include <QtCore/QDebug>
#include <QtCore/QSortFilterProxyModel>
#include <QtCore/QThread>
#include <QtGui/QCloseEvent>
#include <QtGui/QStandardItemModel>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMessageBox>
// Hb
#include <HbGlobal.h>
#include <HbServer.h>
// Local
#include <ServerAuthStrategy.h>
#include <ServerChatChannel.h>
#include <ServerMainWindow.h>
#include <ServerSumChannel.h>

using namespace hb::link;
using namespace hb::network;
using namespace hb::networkexample;

QString ServerMainWindow::msClientId = "940633959281250";                      // Fake value.
QString ServerMainWindow::msClientSecret = "74621eedf9aa2cde9cd31dc5c4d3c440"; // Fake value.

ServerMainWindow::ServerMainWindow(QWidget* parent) : QMainWindow(parent) {
    HbO2ServerConfig facebook_config;
    facebook_config.setClientId(msClientId);
    facebook_config.setClientSecret(msClientSecret);

    HbO2ServerConfig google_config;
    google_config.setClientId(msClientId);
    google_config.setClientSecret(msClientSecret);

    HbGeneralServerConfig config;
    config.setAppName("hb-network-example");
    config.setProtocolVersion(1);
    config.auth().setAuthMaxTries(3);
    config.auth().setAuthTimeout(30);
    config.auth().enableFacebookAuth(facebook_config);
    config.auth().enableGoogleAuth(google_config);
    config.presence().setWarningAliveThreshold(60);
    config.presence().setKickAliveThreshold(90);

    mHbServer = new HbServer(config);

    mSumChannel = new ServerSumChannel();
    mChatChannel = new ServerChatChannel();

    // Ui
    setupUi(this);
    setWindowTitle("Server");

    connect(ui_qpb_start, &QPushButton::clicked, this, &ServerMainWindow::onStartClicked);
    connect(ui_qpb_stop, &QPushButton::clicked, this, &ServerMainWindow::onStopClicked);

    connect(mHbServer, &HbServer::serverStatusChanged, this, &ServerMainWindow::onServerStatusChanged);
}

ServerMainWindow::~ServerMainWindow() {
}

void ServerMainWindow::onStartClicked() {
    HbTcpServerConfig config;
    config.setAddress(QHostAddress::Any);
    config.setPort(4000);
    config.setMaxUsersPerThread(1);
    config.setBadHeaderTolerant(false);

    config.plugChannel(mSumChannel);
    config.plugChannel(mChatChannel);

    networkuid server_uid = mHbServer->joinTcpServer(config, true);
    if (server_uid > 0) {
        qDebug() << "Server started" << server_uid;
    }
}

void ServerMainWindow::onStopClicked() {
    mHbServer->leave();
}

void ServerMainWindow::onServerStatusChanged(networkuid server_uid, HbNetworkProtocol::ServerStatus status) {
    qDebug() << "Status changed on server" << server_uid << HbNetworkProtocol::MetaServerStatus::toString(status);
}
