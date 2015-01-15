// Qt
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QtCore/QThread>
// Hb
#include <HbLogService.h>
// Local
#include <tcp/HbTcpServer.h>
#include <tcp/HbTcpSocketHandler.h>
#include <tcp/HbTcpSocket.h>

using namespace hb::network;

TcpServer::TcpServer(QObject * parent) :
	QTcpServer( parent )
{
}

void TcpServer::incomingConnection(qint32 socket_descriptor)
{
	HbLogBegin();

	emit newConnection( socket_descriptor );

	HbLogEnd();
}

HbTcpServer::HbTcpServer( QObject * parent )/* :
    HbAbstractServer( parent )*/
{
    _server = q_check_ptr( new TcpServer( this ) );

    connect( _server, &TcpServer::newConnection,
        this, &HbTcpServer::onNewConnection, Qt::UniqueConnection );
}

HbTcpServer::~HbTcpServer()
{
    leave();
}


bool HbTcpServer::join( const HbTcpServerConfig & config )
{
    return ( setConfiguration( config ) ) ? HbAbstractServer::join() : false;
}


bool HbTcpServer::setConfiguration( const HbTcpServerConfig & config )
{
    if( isListening() )
    {
        HbError( "Can not set configuration, server is listening." );

        return false;
    }

	reset();

    _config = config;

    return true;
}

const HbTcpServerConfig & HbTcpServer::configuration() const
{
    return _config;
}

void HbTcpServer::reset()
{

}

bool HbTcpServer::connectToNetwork()
{
	if ( !_server->listen( this->configuration( ).address( ), this->configuration( ).port( ) ) )
    {
        HbError( "Server failed to listen." );
        return false;
    }

    return true;
}

void HbTcpServer::disconnectFromNetwork()
{
    _server->close();
}

bool HbTcpServer::isListening() const
{
    return _server->isListening();
}


/*void HbTcpServer::incomingConnection( HbAbstractSocket * socket )
{
    HbAbstractServer::incomingConnection( socket );
}*/

bool HbTcpServer::disconnectFromNetwork(quint16 uuid )
{
    return true;
    //HbTcpSocket * disconnected = q_dynamic_cast( HbTcpSocket *, uuid );
    //return q_assert_ptr( disconnected )->disconnectFromHost();
}

void HbTcpServer::onNewConnection(qint32 socket_descriptor)
{
	HbLogBegin();

	HbTcpSocketHandler* handler = nullptr;

	// Seeking an available handler.
	foreach(HbTcpSocketHandler * h, mHandlerById.values())
	{
		if (h->canHandleNewConnection())
		{
			handler = h;			
		}
	}

	// We must create one.
	if (!handler)
	{
		handler = new HbTcpSocketHandler( this );

		bool is_threaded = _config.maxUsersPerThread() > 0;
		// Must be threaded.
		if (is_threaded)
		{
			QThread * t = new QThread();
			handler->moveToThread(t);

			connect(t,       &QThread::started,         handler, &HbTcpSocketHandler::init);
			connect(t,       &QThread::finished,        handler, &HbTcpSocketHandler::deleteLater);
			connect(t,       &QThread::finished,        t,       &QThread::deleteLater);

			t->start();

			mHandlerThreads.insert(t, handler);
		}

		mHandlerById.insert(handler->id(), handler);

		HbInfo("New HbTcpSocketHandler#%d created to handle socket#%d added.", handler->id(), socket_descriptor);
	}

	Q_ASSERT( QMetaObject::invokeMethod(handler, "onNewPendingConnection", Q_ARG(qint32, socket_descriptor)) );

	HbLogEnd();
}

