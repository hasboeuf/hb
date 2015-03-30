// Qt
#include <QtCore/QDataStream>
// Hb
#include <HbLogService.h>
// Local
#include <com/HbAbstractClient.h>
#include <com/HbAbstractSocket.h>
#include <config/com/HbNetworkConfig.h>
#include <contract/HbNetworkHeader.h>

using namespace hb::network;


HbAbstractClient::HbAbstractClient(QObject * parent) :
    HbAbstractNetwork( parent )
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

        connect( socket, &HbAbstractSocket::socketConnected,
                 this,   &HbAbstractClient::onSocketConnected, Qt::UniqueConnection);

        connect( socket, &HbAbstractSocket::socketReadyPacket,
                 this,   &HbAbstractClient::onSocketReadyPacket,  Qt::UniqueConnection );

        connect( socket, &HbAbstractSocket::socketDisconnected,
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

        networkuid uid = this->uid(); // Store uid before socket deletion.

        disconnectFromNetwork();

        mReady = false;
        emit clientDisconnected( uid );
    }

    return true;
}

bool HbAbstractClient::isReady() const
{
    return mReady;
}


bool HbAbstractClient::send( ShConstHbNetworkContract contract )
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
                HbError( "Try to send an unregistered contract [service=%d, code=%d]", contract->header().service(), contract->header().code() );

                return false;
            }

            //if ( socket->type() == HbNetworkProtocol::NETWORK_UDP )
            //{
            //    contract->setRouting( HbNetworkProtocol::RoutingScheme::BROADCAST );
            //}

            if( socket->sendContract( contract ) )
            {
                return true;
            }

            // TODO socket error string
        }
    }

    return false;
}

const HbClientConfig & HbAbstractClient::configuration() const
{
    return mConfig;
}

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

    emit clientConnected( uid() );

}

void HbAbstractClient::onSocketReadyPacket()
{
    HbAbstractSocket * socket = q_assert_ptr( dynamic_cast<HbAbstractSocket *>( sender( )) );

    bool available = ( socket->isListening() && socket->packetAvailable() );

    while( available )
    {
        QByteArray packet = socket->readPacket( );

        if( !configuration().openMode( ).testFlag( QIODevice::ReadOnly ) )
        {
            HbError( "Unable to receive contract on write only socket %d.", socket->uid() );
        }
        else
        {
            QDataStream stream( &packet, QIODevice::ReadOnly );

            HbNetworkHeader header;
            stream >> header;
            q_assert( stream.status() == QDataStream::Ok );

            if( !configuration().isBadHeaderTolerant() )
            {
                if( !HbAbstractNetwork::checkHeader( header ) )
                {
                    HbError( "Bad contract header (app=%s, protocol=%d. Disconnection.",
                             HbLatin1( header.appName() ),
                             header.protocolVersion() );
                    leave();
                    return;
                }
            }

            HbNetworkContract * contract = configuration().exchanges().contract( header );

            if( !contract )
            {
                HbError( "Try to read unregistered contract [service=%d, code=%d].", header.service(), header.code() );
            }
            else
            {
                if( !contract->read( stream ) )
                {
                    q_assert( stream.status( ) == QDataStream::Ok );

                    HbError( "Error occurred while reading contract [service=%d, code=%d].", header.service(), header.code() );
                }
                else
                {
                    contract->setSender ( socket->uid() );
                    contract->setNetworkType( type() );
                    contract->updateReply(); // In case of a reply-able contract.

                    emit clientContractReceived( uid(), contract );
                }
            }
        }

        available = ( socket->isListening() && socket->packetAvailable() );
    }
}

void HbAbstractClient::onSocketDisconnected()
{
    networkuid uid = this->uid(); // Store uid before socket deletion.

    qint16 retry_delay = configuration().reconnectionDelay();
    if( retry_delay > 0 )
    {
        if( mRetry == 0 )
        {
            mRetry = startTimer( retry_delay );
        }
    }
    else
    {
        deleteSocket();
    }

    mReady = false;

    emit clientDisconnected( uid );
}
