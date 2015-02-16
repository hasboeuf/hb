// Qt
#include <QtCore/QDataStream>
// Hb
#include <HbLogService.h>
#include <core/HbUuidGenerator.h>
// Local
#include <com/HbAbstractServer.h>
#include <com/HbAbstractSocket.h>
#include <config/com/HbNetworkConfig.h>
#include <contract/HbNetworkHeader.h>
#include <com/HbSocketHandler.h>

using namespace hb::tools;
using namespace hb::network;

HbAbstractServer::HbAbstractServer(QObject * parent) :
	HbAbstractNetwork(parent)
{
    mUuid = HbUuidGenerator< netwuuid, CLASS_NETW >::get()->uuid();
    mReady = false;
}


bool HbAbstractServer::join()
{
	if ( !isListening() )
	{
        if( !this->configuration().isValid() )
		{
            HbError( "Invalid server configuration." );
			return false;
		}

		if ( connectToNetwork() )
		{
            mReady = true;
            emit serverConnected( mUuid );
		}
	}

	return isListening();
}

bool HbAbstractServer::leave()
{
    if ( isListening() )
	{
		disconnectFromNetwork();
        mReady = false;
        emit serverDisconnected( mUuid );

        HbInfo( "Server stopped." );
    }
    else
    {
        HbInfo( "Server already stopped." );
    }

    reset();

    /*QHash< quint32, HbSocketHandler * >::iterator it = mHandlerBySocketId.begin();
    while( it != mHandlerBySocketId.end() )
    {
        quint16 socket_uuid = it.key();
        HbSocketHandler * handler = q_assert_ptr( it.value() );

        leave( socket_uuid ); // TODO delete thread etc.

        ++it;
    }*/


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

		//qDeleteAll(_pending);
		//qDeleteAll(_connected);




	return true;
}

bool HbAbstractServer::leave( quint16 uuid )
{
    HbInfo( "Disconnecting socket %d.", uuid );
    HbSocketHandler * handler = mHandlerBySocketId.value( uuid, nullptr );
    q_assert_ptr( handler );

    bool result = false;
    q_assert( QMetaObject::invokeMethod( handler, "onDisconnectionRequest", Q_ARG( quint16, uuid ) ) );
    return result;

    //QMetaObject::invokeMethod(	handler,
    //							QStringLiteral("onDisconnectRequest"),
    //							Q_ARG( quint16, uuid ) );

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

bool HbAbstractServer::isReady() const
{
    return mReady;
}

quint16 HbAbstractServer::uuid() const
{
    return mUuid;
}


bool HbAbstractServer::send( HbNetworkContract * contract )
{
	if( !contract )
	{
        HbWarning( "Try to send a null contract." );
	}

	else
	{
		if (!isListening())
		{
            HbError( "Unable to send contract on inactive server" );
		}
		else
		{
            return send( contract );
		}
	}

	return false;
}

/*bool HbAbstractServer::reply(int sender, const HbNetworkContract * contract)
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
}*/

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


/*QList< quint16 > HbAbstractServer::connected() const
{
	return mHandlerBySocketId.keys( );
}*/

bool HbAbstractServer::isUuidConnected( quint16 uuid ) const
{
	return mHandlerBySocketId.contains( uuid );
}

const HbServerConfig & HbAbstractServer::configuration() const // SUB
{
    return mConfig;
}

void HbAbstractServer::reset()
{
    HbInfo( "Reset server..." );

    mPending.clear();
    foreach( HbSocketHandler * handler, mHandlerById.values() )
    {
        q_assert_ptr( handler );
        HbInfo( "Deleting handler #%d", handler->id() );
        handler->disconnect();
        handler->deleteLater();
    }
    mPending.clear();
    mHandlerById.clear();
    mHandlerBySocketId.clear();
}

/*bool HbAbstractServer::send( HbNetworkContract * contract )
{
	if( !HbAbstractNetwork::configuration( ).openMode().testFlag( QIODevice::WriteOnly ) )
	{
        HbError( "Unable to send contract on read only server." );
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

        HbError( "Unable to send a contract without receivers." );

	}

	return false;
}*/

/*bool HbAbstractServer::send( int uuid, const HbNetworkPacket & packet )
{
	return true;
}*/

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


void HbAbstractServer::onSocketConnected( qint32 socket_descriptor, sockuuid socket_uuid )
{
    if( !mReady )
    {
        HbInfo( "Server not ready, no treatments for onSocketConnected()." );
        return;
    }
    HbSocketHandler * handler = qobject_cast< HbSocketHandler * >( sender() );
    q_assert_ptr( handler );
    q_assert( mPending.contains( socket_descriptor ) );
    q_assert( !mHandlerBySocketId.contains( socket_uuid ) );

    mPending.removeOne( socket_descriptor );
    mHandlerBySocketId.insert( socket_uuid, handler );
}

void HbAbstractServer::onSocketDisconnected( sockuuid socket_uuid )
{
    if( !mReady )
    {
        HbInfo( "Server not ready, no treatments for onSocketDisconnected()." );
        return;
    }
    HbSocketHandler * handler = qobject_cast< HbSocketHandler * >( sender() );
    q_assert_ptr( handler );
    q_assert( mHandlerBySocketId.value( socket_uuid ) == handler );

    mHandlerBySocketId.remove( socket_uuid );
}

void HbAbstractServer::onSocketContractReceived( sockuuid socket_uuid, const HbNetworkContract * contract )
{
    if( !mReady )
    {
        HbInfo( "Server not ready, no treatments for onSocketContractReceived()." );
        delete contract;
        return;
    }
    emit socketContractReceived( mUuid, socket_uuid, contract );
}

void HbAbstractServer::onHandlerIdled()
{
    if( !mReady )
    {
        HbInfo( "Server not ready, no treatments for onHandlerIdled()." );
        return;
    }
    HbSocketHandler * handler = qobject_cast< HbSocketHandler * >( sender() );
    q_assert_ptr( handler );

    mHandlerById.remove( handler->id() );

    handler->disconnect();
    handler->deleteLater();
}


