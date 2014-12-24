// Qt
#include <QtCore/QTimer>
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

bool HbSocketHandler::canHandleNewConnection() const
{
    HbLogBegin();

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
	// Q_ASSERT( socket->type( ) != HbAbstractSocket::UdpSocket );

	q_assert_ptr( socket );

	mSocketById.insert( socket->uuid( ), socket );
	mIdBySocket.insert( socket, socket->uuid( ) );

	connect( socket, &HbAbstractSocket::readyPacket,  this, &HbSocketHandler::onSocketReadyPacket );
	connect( socket, &HbAbstractSocket::disconnected, this, &HbSocketHandler::onSocketDisconnected );

	connect( socket, (void (HbAbstractSocket::*)(QAbstractSocket::SocketError)) &HbAbstractSocket::error,
		this, [this, socket]( QAbstractSocket::SocketError error )
	{
		server()->raiseError( error, QStringLiteral( "%1 on socket %2" ).
			arg( socket->errorString( ) ).arg( socket->uuid( ) ) );

	}, Qt::UniqueConnection );

	return true;
}


void HbSocketHandler::onSocketReadyPacket()
{
	HbAbstractSocket * socket = q_assert_ptr( dynamic_cast<HbAbstractSocket *>(sender( )) );

	bool available = (socket->isListening( ) &&
		socket->packetAvailable( ));

	while( available )
	{
		QByteArray packet = socket->readPacket( );

		if( !mpServer->configuration().openMode( ).testFlag( QIODevice::ReadOnly ) )
		{
			mpServer->raiseError( QAbstractSocket::OperationError,
				QStringLiteral( "unable to receive contract on write only socket %1" ).arg( socket->uuid( ) ) );
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
				mpServer->raiseError( QAbstractSocket::UnknownSocketError,
					QStringLiteral( "try to read unregistered contract %1::%2" ).arg( service ).arg( code ) );
			}
			else if( !contract->read( stream ) )
			{
				Q_ASSERT( stream.status( ) == QDataStream::Ok );

				mpServer->raiseError( QAbstractSocket::UnknownSocketError,
					QStringLiteral( "error occurred while reading contract %1::%2" ).arg( service ).arg( code ) );
			}

			else
			{
				//bool processing = ((header.routing( ) == HbNetworkContract::RoutingScheme::Unicast) &&
				//	(header.receivers( ).isEmpty( ) || header.receivers( ).contains( _uuid )));

				//emit contractReceived( socket->uuid(), contract );
			}
		}

		available = (socket->isListening( ) &&
			socket->packetAvailable( ));
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

	disconnect( socket, &HbAbstractSocket::readyPacket, this, nullptr );
	disconnect( socket, &HbAbstractSocket::disconnected, this, nullptr );

    socket->deleteLater();

	emit socketDisconnected( id );

    HbLogEnd();

}
