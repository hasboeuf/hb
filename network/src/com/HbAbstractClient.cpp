// Qt
#include <QtCore/QDataStream>
// Hb
#include <HbLogService.h>
// Local
#include <com/HbAbstractClient.h>
#include <com/HbAbstractSocket.h>
#include <config/HbNetworkConfig.h>
#include <contract/HbNetworkHeader.h>

using namespace hb::network;


HbAbstractClient::HbAbstractClient(QObject * parent) :
	HbAbstractNetwork(parent)
{
    mRetry = 0;
    mReady = false;
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
        if ( mRetry )
		{
            killTimer( mRetry );
            mRetry = 0;
		}

		HbAbstractSocket * socket = currentConnection();

        socket->disconnect();

		if ( !disconnectFromNetwork() )
		{
            HbError( "Can not disconnect from network." );
			return false;
		}

        mReady = false;
		emit disconnected();
	}

	return true;
}

bool HbAbstractClient::isReady() const
{
    return mReady;
}


bool HbAbstractClient::send( HbNetworkContract *contract )
{
    if ( !contract )
    {
        HbWarning( "Try to send a null contract." );
    }
	else
	{
		HbAbstractSocket * socket = currentConnection();

        if ( !socket || !socket->isListening() )
		{
            HbError( "Unable to send contract on null/inactive socket." );
		}

        else if( !this->configuration().openMode().testFlag( QIODevice::WriteOnly ) )
		{
            HbError( "Unable to send contract on read only socket." );
		}

		else
		{
            if ( !configuration().exchanges().registered( contract->header().service(), contract->header().code() ) )
			{
                HbError( "Try to send an unregistered contract [service=%d, code=%d", contract->header().service(), contract->header().code() );

				return false;
			}

            //if ( socket->type() == HbNetworkProtocol::NETWORK_UDP )
            //{
            //    contract->setRouting( HbNetworkProtocol::RoutingScheme::BROADCAST );
            //}

			QByteArray buffer;
			QString socketError;

			QDataStream stream(&buffer, QIODevice::WriteOnly);
            stream << contract->header();

            if ( !contract->write( stream ) )
            {
                HbError( "Invalid contract format." );
            }
			else
			{
				qint64 bytesWritten = socket->writePacket(buffer);

                if ( bytesWritten > 0 )
					return true;

                q_assert( bytesWritten );
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
    if ( mRetry )
	{
        killTimer( mRetry );
        mRetry = 0;
	}

	emit connected();

}

void HbAbstractClient::onSocketContractReceived( const HbNetworkContract * contract)
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

            //if( header.routing() != HbNetworkProtocol::RoutingScheme::BROADCAST )
            //{
            //	q_assert(header.receivers().contains(configuration().uuid()));
            //}

            HbNetworkContract * contract = configuration().exchanges().contract( header );

            if ( !contract )
			{
                HbError( "Try to read unregistered contract." );
			}

			else if (!contract->read(stream))
			{
                q_assert( stream.status() == QDataStream::Ok );

                HbError( "Error occurred while reading contract [service=%d, code=%d", header.service(), header.code() );
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
        killTimer( mRetry );
        mRetry = startTimer( retry_delay );
    }
    else
    {
        deleteSocket();
    }

    mReady = false;

    emit disconnected();
}
