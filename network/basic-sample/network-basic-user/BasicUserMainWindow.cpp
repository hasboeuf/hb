// Qt
// Hb
#include <HbGlobal.h>
// Local
#include <BasicUserMainWindow.h>
#include <MessageContract.h>
#include <RequestContract.h>
#include <ResponseContract.h>

using namespace hb::tools;
using namespace hb::network;
using namespace hb::networkexample;

BasicUserMainWindow::BasicUserMainWindow(QWidget* parent) : QMainWindow(parent) {
    // Ui
    setupUi(this);
    setWindowTitle("BasicUser");

    HbNetworkProtocol::msAppName = "HbBasicNetworkExample";
    HbNetworkProtocol::msProtocolVersion = 1;

    connect(ui_qpb_start, &QPushButton::clicked, this, &BasicUserMainWindow::onStartClicked);
    connect(ui_qpb_send_contract, &QPushButton::clicked, this, &BasicUserMainWindow::onSendContractClicked);
    connect(ui_qpb_stop, &QPushButton::clicked, this, &BasicUserMainWindow::onStopClicked);

    connect(&mTcpClient, &HbTcpClient::clientConnected, this, &BasicUserMainWindow::onClientConnected);
    connect(&mTcpClient, &HbTcpClient::clientDisconnected, this, &BasicUserMainWindow::onClientDisconnected);
    connect(&mTcpClient, &HbTcpClient::clientContractReceived, this, &BasicUserMainWindow::onClientContractReceived);
}

void BasicUserMainWindow::onStartClicked() {
    HbTcpClientConfig config;
    config.setAddress(QHostAddress::LocalHost);
    config.setPort(4001);
    config.setReconnectionDelay(1000);
    config.setBadHeaderTolerant(false);

    config.exchanges().plug<RequestContract>();
    config.exchanges().plug<ResponseContract>();
    config.exchanges().plug<MessageContract>();

    mTcpClient.join(config);
}

void BasicUserMainWindow::onSendContractClicked() {
    qDebug() << "Send request contract";

    RequestContract* request = new RequestContract();
    request->setRequest("What ever im asking, ill get the same response");

    mTcpClient.send(ShConstHbNetworkContract(request));
}

void BasicUserMainWindow::onStopClicked() {
    mTcpClient.leave();
}

void BasicUserMainWindow::onClientConnected(networkuid client_uid) {
    qDebug() << "Client connected" << client_uid;
}

void BasicUserMainWindow::onClientDisconnected(networkuid client_uid) {
    qDebug() << "Client disconnected" << client_uid;
}

void BasicUserMainWindow::onClientContractReceived(networkuid client_uid, const HbNetworkContract* contract) {
    q_assert_ptr(contract);

    qDebug() << "Contract received on client" << client_uid;
    qDebug() << "Contract details:" << contract->toString();

    const ResponseContract* response = contract->value<ResponseContract>();
    if (response) {
        qDebug() << "Contract is of type ResponseContract";
    }

    const MessageContract* message = contract->value<MessageContract>();
    if (message) {
        qDebug() << "Contract is of type MessageContract";
    }

    delete contract;
}
