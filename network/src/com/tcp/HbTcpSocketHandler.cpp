// Qt
#include <QtCore/QTimer>
#include <QtNetwork/QTcpSocket>
// Hb
#include <HbGlobal.h>
#include <HbUuidGenerator.h>
#include <HbLogService.h>
// Local
#include <com/tcp/HbTcpSocketHandler.h>
#include <com/tcp/HbTcpServer.h>
#include <com/tcp/HbTcpSocket.h>
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
    reset();
}

HbTcpServer * HbTcpSocketHandler::server() const
{
	return mpServer;
}

void HbTcpSocketHandler::init()
{
    HbSocketHandler::init();
}

void HbTcpSocketHandler::reset()
{
    HbSocketHandler::reset();
}

void HbTcpSocketHandler::onNewPendingConnection( qint32 socket_descriptor )
{
    HbLogBegin();

    if( !canHandleNewConnection() )
    {
        HbError("SocketHandler#%d: Cannot handle socket#%d.", mId, socket_descriptor);
        // Creating a volatile socket to disconnect the descriptor.
        QTcpSocket * socket = new QTcpSocket();
        socket->setSocketDescriptor(socket_descriptor);
		socket->close();
        delete socket;

        HbLogEnd();
        return;
	}

    QTcpSocket * device = q_assert_ptr( new QTcpSocket() );
    q_assert( device->setSocketDescriptor( socket_descriptor ) );

    HbTcpSocket * socket = new HbTcpSocket( device );

	HbTcpConfig::SocketOptions options = mpServer->configuration().options();
	socket->setSocketOption( QAbstractSocket::LowDelayOption, options.testFlag( HbTcpConfig::SocketOption::LowDelay ) );
	socket->setSocketOption( QAbstractSocket::KeepAliveOption, options.testFlag( HbTcpConfig::SocketOption::KeepAlive ) );
	socket->setSocketOption( QAbstractSocket::MulticastLoopbackOption, options.testFlag( HbTcpConfig::SocketOption::MulticastLoopback ) );

    storeNewSocket( socket, socket_descriptor );

    HbInfo( "HbTcpSocketHandler#%d: New socket#%d added.", mId, socket_descriptor );

    HbLogEnd();
}
