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

    HbLogEnd();
}

HbTcpSocketHandler::~HbTcpSocketHandler()
{
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
        //return HbNetworkError::TCPSOCKETHANDLER_FULL;
     }

	q_assert( !mSocketById.contains( socket_descriptor ) );

	QTcpSocket* device = q_assert_ptr( new QTcpSocket() );
	q_assert( device->setSocketDescriptor(socket_descriptor) );

    HbTcpSocket *socket = new HbTcpSocket( device );

    HbInfo("SocketHandler#%d: New socket#%d added.", mId, socket_descriptor);

	storeNewSocket( socket );

    HbLogEnd();
	//return HbNetworkError::G_SUCCESS;
}