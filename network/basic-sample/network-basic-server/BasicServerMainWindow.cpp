// Qt
// Hb
#include <HbGlobal.h>
// Local
#include <BasicServerMainWindow.h>
#include <MessageContract.h>
#include <RequestContract.h>
#include <ResponseContract.h>

using namespace hb::network;
using namespace hb::networkexample;

BasicServerMainWindow::BasicServerMainWindow(QWidget* parent) : QMainWindow(parent) {
    // Ui
    setupUi(this);
    setWindowTitle("BasicServer");

    HbNetworkProtocol::msAppName = "HbBasicNetworkExample";
    HbNetworkProtocol::msProtocolVersion = 1;

    connect(ui_qpb_start, &QPushButton::clicked, this, &BasicServerMainWindow::onStartClicked);
    connect(ui_qpb_send_contract, &QPushButton::clicked, this, &BasicServerMainWindow::onSendContractClicked);
    connect(ui_qpb_stop, &QPushButton::clicked, this, &BasicServerMainWindow::onStopClicked);

    connect(&mTcpServer, &HbTcpServer::serverConnected, this, &BasicServerMainWindow::onServerConnected);
    connect(&mTcpServer, &HbTcpServer::serverDisconnected, this, &BasicServerMainWindow::onServerDisconnected);
    connect(&mTcpServer, &HbTcpServer::socketConnected, this, &BasicServerMainWindow::onSocketConnected);
    connect(&mTcpServer, &HbTcpServer::socketDisconnected, this, &BasicServerMainWindow::onSocketDisconnected);
    connect(&mTcpServer, &HbTcpServer::socketContractReceived, this, &BasicServerMainWindow::onSocketContractReceived);
}

void BasicServerMainWindow::onStartClicked() {
    HbTcpServerConfig config;
    config.setAddress(QHostAddress::Any);
    config.setPort(4001);
    config.setMaxUsersPerThread(1);
    config.setBadHeaderTolerant(false);

    config.exchanges().plug<RequestContract>();
    config.exchanges().plug<ResponseContract>();
    config.exchanges().plug<MessageContract>();

    mTcpServer.join(config);
}

void BasicServerMainWindow::onSendContractClicked() {
    qDebug() << "Send message contract to all sockets";

    MessageContract* message = new MessageContract();
    message->setMessage("Hello world");
    message->setRouting(HbNetworkProtocol::ROUTING_BROADCAST); // To all users.

    mTcpServer.send(ShConstHbNetworkContract(message));
}

void BasicServerMainWindow::onStopClicked() {
    mTcpServer.leave();
}

void BasicServerMainWindow::onServerConnected(networkuid server_uid) {
    qDebug() << "Server connected" << server_uid;
}

void BasicServerMainWindow::onServerDisconnected(networkuid server_uid) {
    qDebug() << "Server disconnected" << server_uid;
}

void BasicServerMainWindow::onSocketConnected(networkuid server_uid, networkuid socket_uid) {
    qDebug() << "Socket" << socket_uid << "connected on server" << server_uid;
}

void BasicServerMainWindow::onSocketDisconnected(networkuid server_uid, networkuid socket_uid) {
    qDebug() << "Socket" << socket_uid << "disconnected on server" << server_uid;
}

void BasicServerMainWindow::onSocketContractReceived(networkuid server_uid,
                                                     networkuid socket_uid,
                                                     const HbNetworkContract* contract) {
    q_assert_ptr(contract);

    qDebug() << "Contract received from socket" << socket_uid << "on server" << server_uid;
    qDebug() << "Contract details:" << contract->toString();

    const RequestContract* request = contract->value<RequestContract>();
    if (request) {
        ResponseContract* response = request->takeReply();

        if (response) {
            response->setResponse("Universal response.");
            mTcpServer.send(ShConstHbNetworkContract(response));
        }
    }

    delete contract;
}
