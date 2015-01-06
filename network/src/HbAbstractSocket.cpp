// Qt
#include <QtCore/QDataStream>
#include <QtCore/QIODevice>
// Hb
#include <HbIdGenerator.h>
// Local
#include <HbAbstractSocket.h>
#include <HbNetworkHeader.h>

using namespace hb::network;
using namespace hb::tools;

HbAbstractSocket::HbAbstractSocket(QIODevice * device)
{
	q_assert_x(_device = device, "HbAbstractSocket::HbAbstractSocket()", "device not defined");

	connect(_device.data(), &QIODevice::readyRead, this,
		&HbAbstractSocket::receive, Qt::UniqueConnection);

	_uuid = HbIdGenerator::get()->getUniqueId();

	_bytesPending = 0;
	_packets.clear();


	_errors.add(QAbstractSocket::ConnectionRefusedError, "connection refused by remote host");
	_errors.add(QAbstractSocket::RemoteHostClosedError, "connection closed by remote host");
	_errors.add(QAbstractSocket::HostNotFoundError, "remote host address not found");
	_errors.add(QAbstractSocket::SocketAccessError, "socket operation not permitted");
	_errors.add(QAbstractSocket::SocketResourceError, "local system ran out of resources");
	_errors.add(QAbstractSocket::SocketTimeoutError, "socket operation timed out");
	_errors.add(QAbstractSocket::DatagramTooLargeError, "UDP datagram larger than operating system's limit");
	_errors.add(QAbstractSocket::NetworkError, "unexpected network error occurred");
	_errors.add(QAbstractSocket::AddressInUseError, "specified address already in use");
	_errors.add(QAbstractSocket::SocketAddressNotAvailableError, "remote host address not available");
	_errors.add(QAbstractSocket::UnsupportedSocketOperationError, "socket operation not supported");
	_errors.add(QAbstractSocket::UnfinishedSocketOperationError, "socket operation still in progress");
	_errors.add(QAbstractSocket::ProxyAuthenticationRequiredError, "proxy authentication required");
	_errors.add(QAbstractSocket::SslHandshakeFailedError, "SSL/TLS handshake failed");
	_errors.add(QAbstractSocket::ProxyConnectionRefusedError, "connection to proxy server not permitted");
	_errors.add(QAbstractSocket::ProxyConnectionClosedError, "connection to proxy server closed");
	_errors.add(QAbstractSocket::ProxyConnectionTimeoutError, "connection to proxy server timed out");
	_errors.add(QAbstractSocket::ProxyNotFoundError, "proxy server address not found");
	_errors.add(QAbstractSocket::ProxyProtocolError, "connection negotiation with proxy server failed");
	_errors.add(QAbstractSocket::OperationError, "socket operation not permitted in %1 state");
	_errors.add(QAbstractSocket::SslInternalError, "SSL internal error occurred");
	_errors.add(QAbstractSocket::SslInvalidUserDataError, "invalid SSL user data used");
	_errors.add(QAbstractSocket::TemporaryError, "temporary error occurred");
	_errors.add(QAbstractSocket::UnknownSocketError, "unknown error");
}

HbAbstractSocket::~HbAbstractSocket()
{
	if (!_device.isNull())
	{
		disconnect(_device.data(), &QIODevice::readyRead, this, nullptr);
		_device->deleteLater();
	}
}


quint16 HbAbstractSocket::uuid() const
{
	return _uuid;
}


QByteArray HbAbstractSocket::readPacket()
{
	return (!_packets.isEmpty()) ? _packets.dequeue() : QByteArray();
}

qint64 HbAbstractSocket::writePacket(const QByteArray & packet) const
{
	if (!packet.isEmpty())
	{
		QByteArray buffer;
		QDataStream stream(&buffer, QIODevice::WriteOnly);

		q_assert(stream.writeBytes(packet.constData(), packet.size()).status() == QDataStream::Ok);
		return writeBuffer(buffer);
	}

	return 0;
}

bool HbAbstractSocket::packetAvailable() const
{
	return (!_packets.isEmpty());
}


QString HbAbstractSocket::errorString() const
{
	return (_errorString.isEmpty()) ? QStringLiteral("unknown error") : _errorString;
}


qint64 HbAbstractSocket::readStream(QDataStream & stream)
{
	qint64 bytesRead = 0;
	quint32 expected = (!_bytesPending) ? sizeof(quint32) : _bytesPending;

	while (stream.device()->bytesAvailable() >= expected) // Multi packets.
	{
		if (!_bytesPending)
		{
			q_assert((stream >> _bytesPending).status() == QDataStream::Ok);
			expected = _bytesPending;
		}

		if (expected > 0)
		{

			if (stream.device()->bytesAvailable() >= expected)
			{

				QByteArray buffer = stream.device()->read(expected);

				if (buffer.isEmpty())
				{
					_errorString = stream.device()->errorString();
					bytesRead = -1;
				}
				else
				{
					_packets.enqueue(buffer);
					bytesRead += expected;
				}

				_bytesPending = 0;
				expected = sizeof(quint32);
			}
		}

		if (bytesRead < 0)
		{
			stream.device()->readAll();
			_packets.clear();

			return bytesRead;
		}
	}

	if( _packets.size() > 0 )
	{
		emit readyPacket();
	}

	return bytesRead;
}

qint64 HbAbstractSocket::writeBuffer(const QByteArray & buffer) const
{
	return (!buffer.isEmpty()) ? _device->write(buffer) : 0;
}


void HbAbstractSocket::setErrorString(const QString & message)
{
	_errorString = message;
}

void HbAbstractSocket::setErrorString(QAbstractSocket::SocketError error)
{
	if (error != QAbstractSocket::OperationError)
		setErrorString(_errors(error));

	else
	{
		QString state = QStringLiteral("unconnected");

		switch (this->state())
		{
		case QAbstractSocket::HostLookupState: state = QStringLiteral("host name lookup"); break;
		case QAbstractSocket::ConnectingState: state = QStringLiteral("connecting"); break;
		case QAbstractSocket::ConnectedState:  state = QStringLiteral("connected"); break;
		case QAbstractSocket::BoundState:      state = QStringLiteral("bound"); break;
		case QAbstractSocket::ClosingState:    state = QStringLiteral("closing"); break;
		case QAbstractSocket::ListeningState:  state = QStringLiteral("listening"); break;
		default:                              break;
		}

		setErrorString(_errors(error).arg(state));
	}
}
