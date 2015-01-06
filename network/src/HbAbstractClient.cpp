// Qt
#include <QtCore/QDataStream>
// Local
#include <HbAbstractClient.h>
#include <HbAbstractSocket.h>
#include <HbNetworkConfig.h>
#include <HbNetworkHeader.h>
#include <IHbNetworkListener.h>


using namespace hb::network;


HbAbstractClient::HbAbstractClient(QObject * parent) :
	HbAbstractNetwork(parent)
{
	_retry = 0;
	_ready = false;
}


bool HbAbstractClient::join()
{
	if (!currentConnection())
	{
		if ( !this->configuration( ).isValid( ) )
		{
			raiseError(QAbstractSocket::ConnectionRefusedError,
				QStringLiteral("invalid client configuration"));

			return false;
		}

		HbAbstractSocket * socket = pendingConnection();

		//connect(socket, &HbAbstractSocket::connected,
		//	this, &HbAbstractClient::onClientConnected, Qt::UniqueConnection);

		if (!connectToNetwork())
		{
			if( this->configuration( ).timeout( ).reconnection > 0 )
				_retry = startTimer( this->configuration().timeout().reconnection );

			raiseError(socket->error(), socket->errorString());
			return false;
		}
	}

	return true;
}

bool HbAbstractClient::leave()
{
	if (currentConnection())
	{
		if (_retry)
		{
			killTimer(_retry);
			_retry = 0;
		}

		HbAbstractSocket * socket = currentConnection();

		disconnect(socket, &HbAbstractSocket::readyPacket,  this, nullptr);
		disconnect(socket, &HbAbstractSocket::disconnected, this, nullptr);

		if (!disconnectFromNetwork())
		{
			raiseError(socket->error(), socket->errorString());
			return false;
		}

		_ready = false;
		emit disconnected();
	}

	return true;
}

bool HbAbstractClient::ready() const
{
	return _ready;
}


bool HbAbstractClient::send(const HbNetworkContract * contract)
{
	if (!contract)
		qWarning("HbAbstractClient::send() -> try to send a null contract");

	else
	{
		HbAbstractSocket * socket = currentConnection();

		if (!socket || !socket->isListening())
		{
			raiseError(QAbstractSocket::OperationError,
				QStringLiteral("unable to send contract on inactive socket"));
		}

		else if( !this->configuration( ).openMode( ).testFlag( QIODevice::WriteOnly ) )
		{
			raiseError(QAbstractSocket::OperationError,
				QStringLiteral("unable to send contract on read only socket"));
		}

		else
		{
			if (!exchanges().registered(contract->service(), contract->code()))
			{
				raiseError(QAbstractSocket::OperationError,
					QStringLiteral("try to send unregistered contract %1::%2").
					arg(contract->service()).arg(contract->code()));

				return false;
			}

			if (socket->type() == HbAbstractSocket::UdpSocket)
				const_cast< HbNetworkContract * >(contract)->setRouting(HbNetworkContract::RoutingScheme::Broadcast);

			QByteArray buffer;
			QString socketError;

			QDataStream stream(&buffer, QIODevice::WriteOnly);
			stream << HbNetworkHeader( this->configuration( ).uuid( ), contract );

			if (!contract->write(stream))
				socketError = QStringLiteral("invalid contract format");

			else
			{
				qint64 bytesWritten = socket->writePacket(buffer);

				if (bytesWritten > 0)
					return true;

				q_assert(bytesWritten);
				socketError = socket->errorString();
			}

			q_assert(stream.status() == QDataStream::Ok);

			raiseError(socket->error(), QStringLiteral("error occurred while sending contract %1::%2: %3").
				arg(contract->service()).arg(contract->code()).arg(socketError));
		}
	}

	return false;
}

/*bool HbAbstractClient::reply(int sender, const HbNetworkContract * contract)
{
	if (!contract || !contract->reply())
		qWarning("HbAbstractClient::reply() -> try to send a null contract");

	else
	{
		HbNetworkContract * reply = contract->reply();

		if (reply->setReceiver(sender))
			return send(reply);
	}

	return false;
}*/


void HbAbstractClient::timerEvent(QTimerEvent * event)
{
	Q_UNUSED(event);
	connectToNetwork();
}


void HbAbstractClient::onConnected()
{
	if (_retry)
	{
		killTimer(_retry);
		_retry = 0;
	}

	HbAbstractSocket * socket = q_assert_ptr(currentConnection());
	disconnect(socket, &HbAbstractSocket::connected, this, nullptr);

	//connect(socket, &HbAbstractSocket::readyPacket,
	//	this, &HbAbstractClient::onContractReceived, Qt::UniqueConnection);

	connect(socket, &HbAbstractSocket::disconnected,
		this, &HbAbstractClient::onDisconnected, Qt::UniqueConnection);

	emit connected();


	if( socket->type() == HbAbstractSocket::UdpSocket )
	{
		//onClientRegistered();
	}
	else
	{
		QByteArray buffer;

		QDataStream stream(&buffer, QIODevice::WriteOnly);
		stream << HbNetworkHeader( this->configuration( ).uuid( ) );

		if (socket->writePacket(buffer) < 0)
		{
			q_assert(stream.status() == QDataStream::Ok);
			qWarning("HbAbstractClient::onClientConnected() -> %s", HbLatin1(socket->errorString()));
		}
	}
}

//void HbAbstractClient::onClientRegistered()
//{
//	HbAbstractSocket * socket = q_assert_ptr(currentConnection());
//
//	if (socket->isListening())
//	{
//		_ready = true;
//		emit registered();
//	}
//}

void HbAbstractClient::onContractReceived( const HbNetworkContract & contract)
{
	HbAbstractSocket * socket = q_assert_ptr(currentConnection());
	bool available = (socket->isListening() && socket->packetAvailable());

	while (available)
	{
		QByteArray packet = socket->readPacket();

		if( !this->configuration( ).openMode( ).testFlag( QIODevice::ReadOnly ) )
		{
			raiseError(QAbstractSocket::OperationError,
				QStringLiteral("unable to receive contract on write only socket"));
		}

		else
		{
			QDataStream stream(&packet, QIODevice::ReadOnly);

			HbNetworkHeader header;
			q_assert((stream >> header).status() == QDataStream::Ok);
			q_assert(header.sender() != configuration().uuid());

			if (header.routing() != HbNetworkContract::RoutingScheme::Broadcast)
				q_assert(header.receivers().contains(configuration().uuid()));

			HbNetworkContract::Service service = header.service();
			HbNetworkContract::Code code = header.code();

			HbNetworkContract * contract = exchanges().contract(service, code);

			if (!contract)
			{
				raiseError(QAbstractSocket::UnknownSocketError,
					QStringLiteral("try to read unregistered contract %1::%2").arg(service).arg(code));
			}

			else if (!contract->read(stream))
			{
				q_assert(stream.status() == QDataStream::Ok);

				raiseError(QAbstractSocket::UnknownSocketError,
					QStringLiteral("error occurred while reading contract %1::%2").arg(service).arg(code));
			}

			else
			{
				//foreach(IHbNetworkListener * listener, listeners())
				//{
				//	listener->receive(header.sender(), contract);
				//}
			}
		}

		available = (socket->isListening() && socket->packetAvailable());
	}
}

void HbAbstractClient::onDisconnected()
{
	HbAbstractSocket * socket = q_assert_ptr(currentConnection());
	disconnect( socket, &HbAbstractSocket::readyPacket, this, nullptr );

	_ready = false;
	emit disconnected();

	//connect(socket = pendingConnection(), &HbAbstractSocket::connected,
	//	this, &HbAbstractClient::onClientConnected, Qt::UniqueConnection);
	
	if (!connectToNetwork())
	{
		if (configuration().timeout().reconnection > 0)
			_retry = startTimer(configuration().timeout().reconnection);
	}
}
