// Qt
#include <QtNetwork/QTcpSocket>
// Local
#include <tcp/HbTcpClient.h>
#include <tcp/HbTcpSocket.h>

using namespace hb::network;


HbTcpClient::HbTcpClient( QObject * parent ) :
    HbAbstractClient( parent )
{
    _socket = nullptr;
}

HbTcpClient::~HbTcpClient()
{
    leave();
}


bool HbTcpClient::join( const HbTcpConfig & config )
{
    return ( setConfiguration( config ) ) ? HbAbstractClient::join() : false;
}


bool HbTcpClient::setConfiguration( const HbTcpConfig & config )
{
    if( _socket )
    {
        raiseError( QAbstractSocket::OperationError,
            QStringLiteral( "unable to set a client configuration when joined" ) );

        return false;
    }

    _config = config;
    return true;
}

const HbTcpConfig & HbTcpClient::configuration() const
{
    return _config;
}


bool HbTcpClient::connectToNetwork()
{
    if( !q_assert_ptr( _socket )->connectToHost( this->configuration() ) )
    {
        raiseError( _socket->error(), _socket->errorString() );
        return false;
    }

    return true;
}

bool HbTcpClient::disconnectFromNetwork()
{
    if( !q_assert_ptr( _socket )->disconnectFromHost() )
        raiseError( _socket->error(), _socket->errorString() );

    else
    {
        _socket->deleteLater();
        _socket = nullptr;
    }

    return ( !_socket );
}


HbAbstractSocket * HbTcpClient::pendingConnection()
{
    q_delete_ptr( &_socket );

    QTcpSocket * device = q_check_ptr( new QTcpSocket( this ) );
    _socket = q_check_ptr( new HbTcpSocket( device ) );

    connect( _socket, ( void ( HbTcpSocket::* )( QAbstractSocket::SocketError ) ) &HbTcpSocket::error,
        this, [this]( QAbstractSocket::SocketError error ) { raiseError( error, _socket->errorString() ); }, Qt::UniqueConnection );

    HbTcpConfig::SocketOptions options = _config.options();

    _socket->setSocketOption( QAbstractSocket::LowDelayOption, options.testFlag( HbTcpConfig::SocketOption::LowDelay ) );
    _socket->setSocketOption( QAbstractSocket::KeepAliveOption, options.testFlag( HbTcpConfig::SocketOption::KeepAlive ) );
    _socket->setSocketOption( QAbstractSocket::MulticastLoopbackOption, options.testFlag( HbTcpConfig::SocketOption::MulticastLoopback ) );

    return _socket;
}

HbAbstractSocket * HbTcpClient::currentConnection() const
{
    return _socket;
}
