// Qt
#include <QtCore/QDataStream>
// Hb
#include <HbLogService.h>
// Local
#include <com/HbAbstractClient.h>
#include <com/HbAbstractSocket.h>
#include <config/HbNetworkConfig.h>
#include <contract/HbNetworkHeader.h>
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
	if ( !currentConnection() )
	{
		if ( !this->configuration( ).isValid( ) )
		{
            HbError( "Invalid client configuration." );

			return false;
		}

        HbAbstractSocket * socket = pendingConnection();

        connect(socket, &HbAbstractSocket::socketConnected,
                this,   &HbAbstractClient::onSocketConnected, Qt::UniqueConnection);

        connect(socket, &HbAbstractSocket::socketDisconnected,
                this,   &HbAbstractClient::onSocketDisconnected, Qt::UniqueConnection);

        if( !connectToNetwork() )
		{
            HbError( "Can not connect to network." );
			return false;
		}
	}

	return true;
}

bool HbAbstractClient::leave()
{
	if ( currentConnection() )
	{
		if ( _retry )
		{
			killTimer( _retry );
			_retry = 0;
		}

		HbAbstractSocket * socket = currentConnection();

        socket->disconnect();

		if ( !disconnectFromNetwork() )
		{
            HbError( "Can not disconnect from network." );
			return false;
		}

		_ready = false;
		emit disconnected();
	}

	return true;
}

bool HbAbstractClient::isReady() const
{
	return _ready;
}


bool HbAbstractClient::send(const HbNetworkContract * contract)
{
    if ( !contract )
    {
		qWarning("HbAbstractClient::send() -> try to send a null contract");
    }
	else
	{
		HbAbstractSocket * socket = currentConnection();

		if (!socket || !socket->isListening())
		{
            HbError( "Unable to send contract on null/inactive socket." );
		}

		else if( !this->configuration( ).openMode( ).testFlag( QIODevice::WriteOnly ) )
		{
            HbError( "Unable to send contract on read only socket." );
		}

		else
		{
			if (!exchanges().registered(contract->service(), contract->code()))
			{
                HbError( "Try to send an unregistered contract [service=%d, code=%d", contract->service(), contract->code() );

				return false;
			}

			if (socket->type() == HbAbstractSocket::UdpSocket)
				const_cast< HbNetworkContract * >(contract)->setRouting(HbNetworkContract::RoutingScheme::Broadcast);

			QByteArray buffer;
			QString socketError;

			QDataStream stream(&buffer, QIODevice::WriteOnly);
			stream << HbNetworkHeader( this->configuration( ).uuid( ), contract );

			if (!contract->write(stream))
            {
                HbError( "Invalid contract format." );
            }

			else
			{
				qint64 bytesWritten = socket->writePacket(buffer);

				if (bytesWritten > 0)
					return true;

				q_assert(bytesWritten);
				socketError = socket->errorString();
			}

			q_assert(stream.status() == QDataStream::Ok);
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

    if( !connectToNetwork() )
    {
        HbError( "Can not connect to network." );
    }
}


void HbAbstractClient::onSocketConnected()
{
	if (_retry)
	{
		killTimer(_retry);
		_retry = 0;
	}

	emit connected();

}

void HbAbstractClient::onSocketContractReceived( const HbNetworkContract & contract)
{
	HbAbstractSocket * socket = q_assert_ptr(currentConnection());
	bool available = (socket->isListening() && socket->packetAvailable());

	while (available)
	{
		QByteArray packet = socket->readPacket();

		if( !this->configuration( ).openMode( ).testFlag( QIODevice::ReadOnly ) )
		{
            HbError( "Unable to receive contract on write only socket." );
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

            if ( !contract )
			{
                HbError( "Try to read unregistered contract." );
			}

			else if (!contract->read(stream))
			{
                q_assert( stream.status() == QDataStream::Ok );

                HbError( "Error occurred while reading contract [service=%d, code=%d", service, code );
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

void HbAbstractClient::onSocketDisconnected()
{
    qint16 retry_delay = configuration().timeout().reconnection;
    if( retry_delay > 0 )
    {
        killTimer( _retry );
        _retry = startTimer( retry_delay );
    }
    else
    {
        deleteSocket();
    }

    _ready = false;

    emit disconnected();
}
