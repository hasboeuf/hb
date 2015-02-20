// Qt
#include <QtCore/QDataStream>
// Hb
#include <HbLogService.h>
// Local
#include <HbAbstractClient.h>
#include <HbAbstractSocket.h>
#include <config/HbComConfig.h>
#include <contract/HbComHeader.h>

using namespace hb::com;


HbAbstractClient::HbAbstractClient(QObject * parent) :
    HbAbstractCom(parent)
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

        if( !connectToCom() )
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

        if ( !disconnectFromCom() )
        {
            HbError( "Can not disconnect from network." );
            return false;
        }

        mReady = false;
        emit clientDisconnected( uid() );
    }

    return true;
}

bool HbAbstractClient::isReady() const
{
    return mReady;
}


bool HbAbstractClient::send( HbComContract *contract )
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

            //if ( socket->type() == HbComProtocol::COM_UDP )
            //{
            //    contract->setRouting( HbComProtocol::RoutingScheme::BROADCAST );
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

const HbClientConfig & HbAbstractClient::configuration() const
{
    return mConfig;
}

/*bool HbAbstractClient::reply(int sender, const HbComContract * contract)
{
    if (!contract || !contract->reply())
        qWarning("HbAbstractClient::reply() -> try to send a null contract");

    else
    {
        HbComContract * reply = contract->reply();

        if (reply->setReceiver(sender))
            return send(reply);
    }

    return false;
}*/


void HbAbstractClient::timerEvent(QTimerEvent * event)
{
    Q_UNUSED(event);

    if( !connectToCom() )
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

    emit clientConnected( uid() );

}

void HbAbstractClient::onSocketContractReceived( const HbComContract * contract)
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

            HbComHeader header;
            q_assert((stream >> header).status() == QDataStream::Ok);

            //if( header.routing() != HbComProtocol::RoutingScheme::BROADCAST )
            //{
            //    q_assert(header.receivers().contains(configuration().uid()));
            //}

            HbComContract * contract = configuration().exchanges().contract( header );

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
                //foreach(IHbComListener * listener, listeners())
                //{
                //    listener->receive(header.sender(), contract);
                //}
            }
        }

        available = (socket->isListening() && socket->packetAvailable());
    }
}

void HbAbstractClient::onSocketDisconnected()
{
    qint16 retry_delay = configuration().reconnectionDelay();
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

    emit clientDisconnected( uid() );
}
