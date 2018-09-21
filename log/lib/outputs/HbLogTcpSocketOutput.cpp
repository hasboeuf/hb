// Qt
#include <QtCore/QTimer>
#include <QtNetwork/QTcpSocket>
// Hb
#include <HbLogMessage.h>
#include <outputs/HbLogTcpSocketOutput.h>

using namespace hb::log;

HbLogTcpSocketOutput::HbLogTcpSocketOutput(const QString& ip, quint16 port, QObject* parent) :
        HbLogAbstractOutput(parent) {
    mIp = ip;
    mPort = port;
}

HbLogTcpSocketOutput::~HbLogTcpSocketOutput() {
    mTcpSocket->close();
}

const QString& HbLogTcpSocketOutput::ip() const {
    return mIp;
}

quint16 HbLogTcpSocketOutput::port() const {
    return mPort;
}

void HbLogTcpSocketOutput::init() {
    mTcpSocket.reset(new QTcpSocket());

    connect(mTcpSocket.data(), &QTcpSocket::stateChanged, this, [this]() {
        auto state = mTcpSocket->state();
        if (state == QTcpSocket::UnconnectedState) {
            QTimer::singleShot(5000, this, &HbLogTcpSocketOutput::onReconnection);
        } else if (state == QTcpSocket::ConnectedState) {
            std::cout << "HbLog: tcp output connected " << qUtf8Printable(mIp) << " " << mPort << std::endl;
        }
    });

    connect(mTcpSocket.data(), &QTcpSocket::disconnected, this, [this]() {
        std::cout << "HbLog: tcp output disconnected " << qUtf8Printable(mIp) << " " << mPort << std::endl;
    });

    onReconnection();
}

void HbLogTcpSocketOutput::processMessage(const HbLogMessagePtr& message) {
    if (mTcpSocket->state() == QAbstractSocket::ConnectedState) {
        std::cout << mTcpSocket->write(message->toByteArray());
        mTcpSocket->flush();
    }
}

void HbLogTcpSocketOutput::onReconnection() {
    if (mTcpSocket->state() == QAbstractSocket::UnconnectedState) {
        mTcpSocket->connectToHost(mIp, mPort);
    }
}
