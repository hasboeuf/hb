// Qt
#include <QtCore/QIODevice>
// Hb
#include <HbLogService.h>
// Local
#include <com/HbAbstractSocket.h>
#include <contract/HbNetworkHeader.h>

using namespace hb::network;
using namespace hb::tools;

HbAbstractSocket::HbAbstractSocket(QIODevice* device, QObject* parent) : QObject(parent) {
    Q_ASSERT(device);
    mDevice = device;

    connect(mDevice.data(), &QIODevice::readyRead, this, &HbAbstractSocket::onReadyRead, Qt::UniqueConnection);

    mBytesPending = 0;
    mPackets.clear();
}

HbAbstractSocket::~HbAbstractSocket() {
    if (!mDevice.isNull()) {
        mDevice.data()->disconnect(); // Disconnect all signals.
        mDevice.data()->close();
        mDevice.data()->deleteLater();
    }
}

bool HbAbstractSocket::sendContract(ShConstHbNetworkContract contract) {
    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::WriteOnly);

    stream << contract->header();
    if (!contract->write(stream)) {
        qWarning() << "Invalid contract format";
    } else {
        qint64 bytesWritten = writePacket(buffer);

        if (bytesWritten > 0) {
            return true;
        }

        Q_ASSERT(bytesWritten);
    }

    Q_ASSERT(stream.status() == QDataStream::Ok);

    return false;
}

QByteArray HbAbstractSocket::readPacket() {
    if (!mPackets.isEmpty()) {
        return mPackets.dequeue();
    }

    qWarning() << "Read an empty packet";
    return QByteArray();
}

qint64 HbAbstractSocket::writePacket(const QByteArray& packet) const {
    if (!packet.isEmpty()) {
        QByteArray buffer;
        QDataStream stream(&buffer, QIODevice::WriteOnly);

        auto status = stream.writeBytes(packet.constData(), packet.size()).status();
        Q_ASSERT(status == QDataStream::Ok);
        return writeBuffer(buffer);
    } else {
        qWarning() << "Try to write an empty packet";
    }

    return 0;
}

bool HbAbstractSocket::packetAvailable() const {
    return (!mPackets.isEmpty());
}

QString HbAbstractSocket::errorString() const {
    if (!mDevice.isNull()) {
        return mDevice.data()->errorString();
    } else {
        return QStringLiteral("");
    }
}

qint64 HbAbstractSocket::readStream(QDataStream& stream) {
    qint64 bytesRead = 0;
    quint32 expected = sizeof(quint32);
    if (mBytesPending > 0) {
        expected = mBytesPending;
    }

    while (stream.device()->bytesAvailable() >= expected) // Multi packets.
    {
        if (mBytesPending == 0) {
            QDataStream::Status status = (stream >> mBytesPending).status();
            Q_ASSERT(status == QDataStream::Ok);

            expected = mBytesPending;
        }
        if (expected > 0) {
            if (stream.device()->bytesAvailable() >= expected) {
                QByteArray buffer = stream.device()->read(expected);

                if (buffer.isEmpty()) {
                    bytesRead = -1;
                } else {
                    mPackets.enqueue(buffer);
                    bytesRead += expected;
                }

                mBytesPending = 0;
                expected = sizeof(quint32);
            }
        }

        if (bytesRead < 0) {
            qWarning() << "No bytes read => packets cleared";
            stream.device()->readAll();
            mPackets.clear();

            return bytesRead;
        }
    }

    if (mPackets.size() > 0) {
        emit socketReadyPacket();
    }

    return bytesRead;
}

qint64 HbAbstractSocket::writeBuffer(const QByteArray& buffer) const {
    Q_ASSERT(!mDevice.isNull());

    if (buffer.isEmpty()) {
        qWarning() << "Try to write an empty buffer";
        return 0;
    }

    return mDevice->write(buffer);
}
