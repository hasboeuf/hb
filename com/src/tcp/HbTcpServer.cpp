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

using namespace hb::com;

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
    mpDevice = q_check_ptr( new TcpServer( this ) );

    connect( mpDevice, &TcpServer::newConnection,
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

    mConfig = config;

    return true;
}

const HbTcpServerConfig & HbTcpServer::configuration() const
{
    return mConfig;
}

void HbTcpServer::reset()
{
    HbAbstractServer::reset();
}

bool HbTcpServer::connectToNetwork()
{
    quint16 port = this->configuration().port();

    if ( !mpDevice->listen( this->configuration().address(), port ) )
    {
        HbError( "Server failed to listen." );
        return false;
    }

    HbInfo( "Server started on port %d.", port );
    return true;
}

void HbTcpServer::disconnectFromNetwork()
{
    mpDevice->close();
}

bool HbTcpServer::isListening() const
{
    return mpDevice->isListening();
}

HbComProtocol::ComType HbTcpServer::type() const
{
    return HbComProtocol::COM_TCP;
}

bool HbTcpServer::disconnectFromNetwork( quint16 uid )
{
    // TODO
    return false;
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

        connect( handler, &HbSocketHandler::socketConnected,        this, &HbAbstractServer::onSocketConnected,        Qt::UniqueConnection );
        connect( handler, &HbSocketHandler::socketDisconnected,     this, &HbAbstractServer::onSocketDisconnected,     Qt::UniqueConnection );
        connect( handler, &HbSocketHandler::socketContractReceived, this, &HbAbstractServer::onSocketContractReceived, Qt::UniqueConnection );
        connect( handler, &HbSocketHandler::handlerIdled,           this, &HbAbstractServer::onHandlerIdled,           Qt::UniqueConnection );

        bool is_threaded = mConfig.maxUsersPerThread() > 0;
        // Must be threaded.
        if (is_threaded)
        {
            QThread * t = new QThread();
            handler->moveToThread( t );

            // TODO better.
            connect(t,       &QThread::started,         handler, &HbSocketHandler::init, Qt::UniqueConnection );
            connect(handler, &QObject::destroyed,       t,       &QThread::quit,         Qt::UniqueConnection );
            connect(t,       &QThread::finished,        t,       &QThread::deleteLater,  Qt::UniqueConnection );

            t->start();
        }

        mHandlerById.insert( handler->uid(), handler );

        HbInfo( "Handler %d created to handle socket %d added.", handler->uid(), socket_descriptor );
    }

    mPending.append( socket_descriptor );
    q_assert( QMetaObject::invokeMethod(handler, "onNewPendingConnection", Q_ARG( qint32, socket_descriptor ) ) );

    HbLogEnd();
}

