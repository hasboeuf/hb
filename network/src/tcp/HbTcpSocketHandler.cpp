// Qt
#include <QtCore/QTimer>
#include <QtNetwork/QTcpSocket>
// Hb
#include <HbGlobal.h>
#include <HbIdGenerator.h>
#include <HbLogService.h>
// Local
#include <tcp/HbTcpSocketHandler.h>
#include <tcp/HbTcpServer.h>
#include <tcp/HbTcpSocket.h>
#include <HbNetworkError.h>

using namespace hb::tools;
using namespace hb::log;
using namespace hb::network;

HbTcpSocketHandler::HbTcpSocketHandler( HbTcpServer * server ) :
	HbSocketHandler( server )
{
    HbLogBegin();

	mpServer = q_assert_ptr( server );

    HbLogEnd();
}

HbTcpSocketHandler::~HbTcpSocketHandler()
{
}

HbTcpServer * HbTcpSocketHandler::server() const
{
	return mpServer;
}

void HbTcpSocketHandler::init()
{

}

void HbTcpSocketHandler::onNewPendingConnection( qint32 socket_descriptor )
{
    HbLogBegin();

    if(!canHandleNewConnection())
    {
        HbError("SocketHandler#%d: Cannot handle socket#%d.", mId, socket_descriptor);
        // Creating a volatile socket to disconnect the descriptor.
        QTcpSocket * socket = new QTcpSocket();
        socket->setSocketDescriptor(socket_descriptor);
		socket->close();
        delete socket;
        HbLogEnd();
		return;
        //return HbNetworkError::TCPSOCKETHANDLER_FULL;
	}

	QTcpSocket* device = q_assert_ptr( new QTcpSocket() );
	q_assert( device->setSocketDescriptor(socket_descriptor) );

    HbTcpSocket * socket = new HbTcpSocket( device );

	HbTcpConfig::SocketOptions options = mpServer->configuration().options();
	socket->setSocketOption( QAbstractSocket::LowDelayOption, options.testFlag( HbTcpConfig::SocketOption::LowDelay ) );
	socket->setSocketOption( QAbstractSocket::KeepAliveOption, options.testFlag( HbTcpConfig::SocketOption::KeepAlive ) );
	socket->setSocketOption( QAbstractSocket::MulticastLoopbackOption, options.testFlag( HbTcpConfig::SocketOption::MulticastLoopback ) );

	storeNewSocket( socket );

	HbInfo( "SocketHandler#%d: New socket#%d added.", mId, socket_descriptor );

	emit socketConnected( socket_descriptor, socket->uuid() ); // To Server.

    HbLogEnd();
	//return HbNetworkError::G_SUCCESS;
}