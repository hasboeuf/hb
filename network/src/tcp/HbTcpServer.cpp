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

HbTcpServer::HbTcpServer( QObject * parent ) :
    HbAbstractServer( parent )
{
    _device = q_check_ptr( new TcpServer( this ) );

    connect( _device, &TcpServer::newConnection,
             this, &HbTcpServer::onNewConnection, Qt::UniqueConnection );
}

HbTcpServer::~HbTcpServer()
{
    leave();
}


bool HbTcpServer::join( const HbTcpServerConfig & config )
{
    if( !setConfiguration( config ) )
    {
        return false;
    }

    return HbAbstractServer::join();
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
    HbAbstractServer::reset();
}

bool HbTcpServer::connectToNetwork()
{
    quint16 port = this->configuration().port();

    if ( !_device->listen( this->configuration().address(), port ) )
    {
        HbError( "Server failed to listen." );
        return false;
    }

    HbInfo( "Server started on port %d.", port );
    return true;
}

void HbTcpServer::disconnectFromNetwork()
{
    _device->close();
}

bool HbTcpServer::isListening() const
{
    return _device->isListening();
}


/*void HbTcpServer::incomingConnection( HbAbstractSocket * socket )
{
    HbAbstractServer::incomingConnection( socket );
}*/

bool HbTcpServer::disconnectFromNetwork(quint16 uuid )
{
    // TODO
    //HbTcpSocket * disconnected = q_dynamic_cast( HbTcpSocket *, uuid );
    //return q_assert_ptr( disconnected )->disconnectFromHost();
}

void HbTcpServer::onNewConnection(qint32 socket_descriptor)
{
	HbLogBegin();

    if( !isReady() )
    {
        HbInfo( "Server not ready, no treatments for onNewConnection()." );
        return;
    }

    HbSocketHandler * handler = nullptr;

	// Seeking an available handler.
    foreach( HbSocketHandler * h , mHandlerById.values() )
	{
        if ( h->canHandleNewConnection() )
		{
            handler = h;
		}
	}

	// We must create one.
    if ( !handler )
	{
		handler = new HbTcpSocketHandler( this );

        connect( handler, &HbSocketHandler::socketConnected,        this, &HbAbstractServer::onSocketConnected );
        connect( handler, &HbSocketHandler::socketDisconnected,     this, &HbAbstractServer::onSocketDisconnected );
        connect( handler, &HbSocketHandler::socketContractReceived, this, &HbAbstractServer::onSocketContractReceived );
        connect( handler, &HbSocketHandler::handlerIdled,           this, &HbAbstractServer::onHandlerIdled );

		bool is_threaded = _config.maxUsersPerThread() > 0;
		// Must be threaded.
		if (is_threaded)
		{
			QThread * t = new QThread();
            handler->moveToThread( t );

            // TODO better.
            connect(t,       &QThread::started,         handler, &HbSocketHandler::init);
            connect(handler, &QObject::destroyed,       t,       &QThread::quit);
			connect(t,       &QThread::finished,        t,       &QThread::deleteLater);

			t->start();
		}

        mHandlerById.insert( handler->id(), handler );

        HbInfo( "New HbTcpSocketHandler#%d created to handle socket#%d added.", handler->id(), socket_descriptor );
	}

    _pending.append( socket_descriptor );
    q_assert( QMetaObject::invokeMethod(handler, "onNewPendingConnection", Q_ARG( qint32, socket_descriptor ) ) );

	HbLogEnd();
}

