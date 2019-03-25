// Qt
#include <QtCore/QTimer>
#include <QtNetwork/QLocalSocket>
// Local
#include <HbLogMessage.h>
#include <outputs/HbLogLocalSocketOutput.h>

using namespace hb::log;

HbLogLocalSocketOutput::HbLogLocalSocketOutput(const QString& name, QObject* parent) : HbLogAbstractOutput(parent) {
    mName = name;
    qRegisterMetaType<QLocalSocket::LocalSocketState>("QLocalSocket::LocalSocketState");
}

HbLogLocalSocketOutput::~HbLogLocalSocketOutput() {
    mLocalSocket->close();
}

const QString& HbLogLocalSocketOutput::name() const {
    return mName;
}

void HbLogLocalSocketOutput::init() {
    mLocalSocket.reset(new QLocalSocket());

    connect(mLocalSocket.data(), &QLocalSocket::stateChanged, this, [this](QLocalSocket::LocalSocketState state) {
        if (state == QLocalSocket::UnconnectedState) {
            QTimer::singleShot(5000, this, &HbLogLocalSocketOutput::onReconnection);
        } else if (state == QLocalSocket::ConnectedState) {
            std::cout << "HbLog: local output connected on " << qUtf8Printable(mName) << std::endl;
        }
    });

    connect(mLocalSocket.data(), &QLocalSocket::disconnected, this, [this]() {
        std::cout << "HbLog: local output disconnected on " << qUtf8Printable(mName) << std::endl;
    });

    onReconnection();
}

void HbLogLocalSocketOutput::processMessage(const HbLogMessagePtr& message) {
    if (mLocalSocket->state() == QLocalSocket::ConnectedState) {
        mLocalSocket->write(message->toByteArray());
        mLocalSocket->flush();
    }
}

void HbLogLocalSocketOutput::onReconnection() {
    if (mLocalSocket->state() == QLocalSocket::UnconnectedState) {
        mLocalSocket->connectToServer(mName);
    }
}
