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

	emit newConnection(socket_descriptor);

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
        raiseError( QAbstractSocket::OperationError, 
            QStringLiteral( "unable to set a server configuration when joined" ) );

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
        raiseError( _server->serverError(), _server->errorString() );
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

bool HbTcpServer::disconnectFromNetwork( HbAbstractSocket * socket )
{
    HbTcpSocket * disconnected = q_dynamic_cast( HbTcpSocket *, socket );
    return q_assert_ptr( disconnected )->disconnectFromHost();
}


void HbTcpServer::onNewConnection(int socket_descriptor)
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

	QMetaObject::invokeMethod(handler, "createNewSocket", Q_ARG(qint32, socket_descriptor));

	HbLogEnd();
    /*QTcpSocket * socket = q_assert_ptr( _server->nextPendingConnection() );

	HbTcpConfig::SocketOptions options = _config.options();

	socket->setSocketOption( QAbstractSocket::LowDelayOption, options.testFlag( HbTcpConfig::SocketOption::LowDelay ) );
    socket->setSocketOption( QAbstractSocket::KeepAliveOption, options.testFlag( HbTcpConfig::SocketOption::KeepAlive ) );
    socket->setSocketOption( QAbstractSocket::MulticastLoopbackOption, options.testFlag( HbTcpConfig::SocketOption::MulticastLoopback ) );
	    
	HbTcpSocket * pending = q_check_ptr( new HbTcpSocket( socket ) );

    connect( pending, ( void ( HbTcpSocket::* )( QAbstractSocket::SocketError ) ) &HbTcpSocket::error,
        this, [this, pending]( QAbstractSocket::SocketError error )
    {
        raiseError( error, QStringLiteral( "%1 on socket %2" ).
            arg( pending->errorString() ).arg( pending->uuid()) );

    }, Qt::UniqueConnection );

    incomingConnection( pending );*/
}

