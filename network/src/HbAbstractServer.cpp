// Qt
#include <QtCore/QDataStream>
// Local
#include <HbAbstractServer.h>
#include <HbAbstractSocket.h>
#include <HbNetworkConfig.h>
#include <HbNetworkHeader.h>
#include <IHbNetworkListener.h>


using namespace hb::network;


HbAbstractServer::HbNetworkPacket::HbNetworkPacket(const HbNetworkHeader * header, const HbNetworkContract * contract)
{
	_header = q_assert_ptr(header);
	_content = q_assert_ptr(contract);
}


const HbNetworkHeader * HbAbstractServer::HbNetworkPacket::header() const
{
	return _header;
}

const HbNetworkContract * HbAbstractServer::HbNetworkPacket::content() const
{
	return _content;
}


HbAbstractServer::HbAbstractServer(QObject * parent) :
	HbAbstractNetwork(parent)
{
	_uuid = 0;
	_ready = false;
}


bool HbAbstractServer::join()
{
	if (!isListening())
	{
		if( !this->configuration( ).isValid( ) )
		{
			raiseError(QAbstractSocket::ConnectionRefusedError,
				QStringLiteral("invalid server configuration"));

			return false;
		}

		if (connectToNetwork())
		{
			_ready = true;
			//emit connected(_uuid = HbAbstractNetwork::configuration().uuid());
		}
	}

	return isListening();
}

bool HbAbstractServer::leave()
{
	if (isListening())
	{
		disconnectFromNetwork();

		// TODO
		//foreach(HbAbstractSocket * socket, _pending)
		//{
		//	disconnect( socket, &HbAbstractSocket::readyPacket, this, nullptr );
		//	disconnect(socket, &HbAbstractSocket::disconnected, this, nullptr);
		//}
		//
		//foreach(HbAbstractSocket * socket, _connected)
		//{
		//	disconnect( socket, &HbAbstractSocket::readyPacket, this, nullptr );
		//	disconnect(socket, &HbAbstractSocket::disconnected, this, nullptr);
		//
		//	emit disconnected(socket->uuid());
		//}

		_uuid = 0;

		//qDeleteAll(_pending);
		//qDeleteAll(_connected);


		_ready = false;
		//emit disconnected( HbAbstractNetwork::configuration( ).uuid( ) );
	}

	return true;
}

bool HbAbstractServer::leave(int uuid)
{
	if (!isListening())
	{
		raiseError(QAbstractSocket::OperationError,
			QStringLiteral("unable to close a client from an inactive server"));
	}

	else
	{
		//HbAbstractSocket * socket = _connected.take(uuid);
		//
		//if (!socket)
		//{
		//	raiseError(QAbstractSocket::OperationError,
		//		QStringLiteral("try to close an unregistered client"));
		//}
		//
		//else
		//{
		//	disconnect( socket, &HbAbstractSocket::readyPacket, this, nullptr );
		//	disconnect(socket, &HbAbstractSocket::disconnected, this, nullptr);
		//
		//	if (!disconnectFromNetwork(socket))
		//	{
		//		//connect(socket, &HbAbstractSocket::disconnected, this,
		//		//	[this, socket]() { onClientDisconnect(socket); }, Qt::UniqueConnection);
		//	}
		//
		//	else
		//	{
		//		emit disconnected(uuid);
		//		return true;
		//	}
		//}
	}

	return false;
}

bool HbAbstractServer::ready() const
{
	return _ready;
}


bool HbAbstractServer::send(const HbNetworkContract * contract)
{
	if (!contract)
		qWarning("HbAbstractServer::send() -> try to send a null contract");

	else
	{
		if (!isListening())
		{
			raiseError(QAbstractSocket::OperationError,
				QStringLiteral("unable to send contract on inactive server"));
		}

		else
		{
			HbNetworkHeader header( HbAbstractNetwork::configuration( ).uuid( ), contract );
			HbNetworkPacket packet(&header, contract);

			return send(packet);
		}
	}

	return false;
}

bool HbAbstractServer::reply(int sender, const HbNetworkContract * contract)
{
	if (!contract || !contract->reply())
		qWarning("HbAbstractServer::reply() -> try to send a null contract");

	else
	{
		HbNetworkContract * reply = contract->reply();

		if (reply->setReceiver(sender))
			return send(reply);
	}

	return false;
}

//bool HbAbstractServer::forward(int receiver, HbNetworkContract * contract)
//{
//	if (!contract)
//		qWarning("HbAbstractServer::forward() -> try to send a null contract");
//
//	else
//	{
//		if (contract->setReceiver(receiver))
//			return send(contract);
//	}
//
//	return false;
//}


QList< int > HbAbstractServer::connected() const
{
	return mHandlerBySocketId.keys( );
}

bool HbAbstractServer::isConnected(int uuid) const
{
	return mHandlerBySocketId.contains( uuid );
}

const HbServerConfig & HbAbstractServer::configuration() const // SUB
{
	return _config;
}

bool HbAbstractServer::send(const HbNetworkPacket & packet)
{
	if( !HbAbstractNetwork::configuration( ).openMode( ).testFlag( QIODevice::WriteOnly ) )
	{
		raiseError(QAbstractSocket::OperationError,
			QStringLiteral("unable to send contract on read only server"));
	}

	else
	{
		const HbNetworkHeader * header = packet.header();

		if (header->routing() == HbNetworkContract::RoutingScheme::Broadcast)
		{
			bool status = true;

			//foreach(HbAbstractSocket * socket, _connected)
			//{
			//	if (socket->uuid() != header->sender())
			//	{
			//		if (socket->isListening())
			//			status &= send(socket, packet);
			//	}

			//	else if (_connected.size() == 1)
			//		return false;
			//}

			return status;
		}

		else if (!header->receivers().isEmpty())
		{
			bool status = true;

			if (header->receivers().size() == 1)
			{
				int addressee = *header->receivers().begin();
				//HbAbstractSocket * socket = _connected.value(addressee);
				//
				//if (addressee == header->sender())
				//{
				//	raiseError(QAbstractSocket::UnknownSocketError,
				//		QStringLiteral("unable to send a contract to owner"));
				//
				//	return false;
				//}
				//
				//if (!socket)
				//{
				//	raiseError(QAbstractSocket::UnknownSocketError,
				//		QStringLiteral("try to send to an unknown receiver"));
				//
				//	return false;
				//}
				//
				//status = send(socket, packet);
			}

			else
			{
				foreach(int addressee, header->receivers())
				{
					//HbAbstractSocket * socket = _connected.value(addressee);
					//
					//if (!socket)
					//{
					//	qWarning("HbAbstractServer::send() -> try to send to an unknown receiver");
					//	status &= false;
					//}
					//
					//else if (addressee != header->sender())
					//{
					//	if (socket->isListening())
					//		status &= send(socket, packet);
					//}
				}
			}

			return status;
		}

		raiseError(QAbstractSocket::UnknownSocketError,
			QStringLiteral("unable to send a contract without receivers"));
	}

	return false;
}

bool HbAbstractServer::send( int uuid, const HbNetworkPacket & packet )
{
	return true;
}

//bool HbAbstractServer::send(HbAbstractSocket * socket, const HbNetworkPacket & packet)
//{
//	if (!socket->isListening())
//	{
//		raiseError(QAbstractSocket::OperationError,
//			QStringLiteral("unable to send contract on inactive socket"));
//	}
//
//	else
//	{
//		const HbNetworkContract * contract = packet.content();
//
//		if (!exchanges().registered(contract->service(), contract->code()))
//		{
//			raiseError(QAbstractSocket::UnknownSocketError,
//				QStringLiteral("try to send unregistered contract %1::%2").arg(contract->service()).arg(contract->code()));
//
//			return false;
//		}
//
//		QByteArray buffer;
//		QString socketError;
//
//		QDataStream stream(&buffer, QIODevice::WriteOnly);
//		stream << *packet.header();
//
//		if (!packet.content()->write(stream))
//			socketError = QStringLiteral("invalid contract format");
//
//		else
//		{
//			qint64 bytesWritten = socket->writePacket(buffer);
//
//			if (bytesWritten > 0)
//				return true;
//
//			Q_ASSERT(bytesWritten != 0);
//			socketError = socket->errorString();
//		}
//
//		Q_ASSERT(stream.status() == QDataStream::Ok);
//
//		raiseError(socket->error(), QStringLiteral("error occurred while sending contract %1::%2 on socket %3: %4").
//			arg(packet.content()->service()).arg(packet.content()->code()).arg(socket->uuid()).arg(socketError));
//	}
//
//	return false;
//}