// Qt
#include <QtCore/QTimer>
#include <QtCore/QMutexLocker>
#include <QtNetwork/QTcpSocket>
// Hb
#include <HbGlobal.h>
#include <HbIdGenerator.h>
#include <HbLogService.h>
// Local
#include <HbSocketHandler.h>
#include <HbAbstractServer.h>
#include <HbAbstractSocket.h>
#include <HbNetworkConfig.h>
#include <HbNetworkError.h>
#include <HbNetworkHeader.h>

using namespace hb::tools;
using namespace hb::log;
using namespace hb::network;

HbSocketHandler::HbSocketHandler( HbAbstractServer * server ) :
	QObject( 0 )
{
    HbLogBegin();

	mId = HbIdGenerator::get()->getUniqueId();
	mState = NOT_THREADED;
	mpServer = q_assert_ptr( server );

    HbLogEnd();
}

HbSocketHandler::~HbSocketHandler()
{
}

HbAbstractServer * HbSocketHandler::server() const
{
	return mpServer;
}

void HbSocketHandler::init()
{
    HbLogBegin();

    mState = THREADED;

    HbLogEnd();
}


quint16 HbSocketHandler::id() const
{
    return mId;
}

bool HbSocketHandler::canHandleNewConnection()
{
    HbLogBegin();

    QMutexLocker locker( &mSocketMutex );

	if (!mpServer->configuration().isThreaded() ||
		(mpServer->configuration().isThreaded() &&
		 mState == THREADED &&
		 mSocketById.size() < mpServer->configuration().maxUsersPerThread() ) )
	{
		return true;
	}

    HbError("SocketHandler#%d: Cannot handle new socket. [state=%d, size=%d, max=%d].",
			mId,
			mState,
			mSocketById.size(),
			mpServer->configuration().maxUsersPerThread() );

    HbLogEnd();
	return false;
}

bool HbSocketHandler::storeNewSocket( HbAbstractSocket * socket )
{
    QMutexLocker locker( &mSocketMutex );

	// Q_ASSERT( socket->type( ) != HbAbstractSocket::UdpSocket );

	q_assert_ptr( socket );

	mSocketById.insert( socket->uuid( ), socket );
	mIdBySocket.insert( socket, socket->uuid( ) );

    connect( socket, &HbAbstractSocket::socketReadyPacket,  this, &HbSocketHandler::onSocketReadyPacket );
    connect( socket, &HbAbstractSocket::socketDisconnected, this, &HbSocketHandler::onSocketDisconnected );
    connect( socket, &HbAbstractSocket::socketError,
             this, [this, socket]()
             {
                 HbError( "Error %d (%s) on socket %d.", socket->error(), HbLatin1( socket->errorString() ), socket->uuid());

             }, Qt::UniqueConnection );

	return true;
}

void HbSocketHandler::onDisconnectRequest( quint16 uuid )
{
	// TODO disconnect socket.
}

void HbSocketHandler::onSocketReadyPacket()
{
	HbAbstractSocket * socket = q_assert_ptr( dynamic_cast<HbAbstractSocket *>(sender( )) );

    bool available = ( socket->isListening() && socket->packetAvailable() );

	while( available )
	{
		QByteArray packet = socket->readPacket( );

		if( !mpServer->configuration().openMode( ).testFlag( QIODevice::ReadOnly ) )
		{
            HbError( "Unable to receive contract on write only socket %d.", socket->uuid() );
		}
		else
		{
			QDataStream stream( &packet, QIODevice::ReadOnly );

			HbNetworkHeader header;
			q_assert( (stream >> header).status( ) == QDataStream::Ok );

			HbNetworkContract::Service service = header.service( );
			HbNetworkContract::Code code       = header.code( );

			HbNetworkContract * contract = mpServer->exchanges( ).contract( service, code );

			if( !contract )
			{
                HbError( "Try to read unregistered contract [service=%d, code=%d].", service, code );
			}
			else if( !contract->read( stream ) )
			{
				Q_ASSERT( stream.status( ) == QDataStream::Ok );

                HbError( "Error occurred while reading contract [service=%d, code=%d].", service, code );
			}
			else
			{
				//bool processing = ((header.routing( ) == HbNetworkContract::RoutingScheme::Unicast) &&
				//	(header.receivers( ).isEmpty( ) || header.receivers( ).contains( _uuid )));

				//emit contractReceived( socket->uuid(), contract );
			}
		}

        available = ( socket->isListening() && socket->packetAvailable() );
	}
}

void HbSocketHandler::onSocketDisconnected()
{
    HbLogBegin();

	HbAbstractSocket * socket = q_assert_ptr( dynamic_cast<HbAbstractSocket *>(sender() ) );

	q_assert( mIdBySocket.contains( socket ) );
	q_assert( mSocketById.contains( socket->uuid( ) ) );

    HbInfo("SocketPool%d: Socket#%d disconnected.", mId, socket->uuid() );

	quint16 id = socket->uuid();

	mIdBySocket.remove( socket );
	mSocketById.remove( id );

    disconnect( socket, nullptr, this, nullptr );

    socket->deleteLater();

	emit socketDisconnected( id );

    HbLogEnd();

}
