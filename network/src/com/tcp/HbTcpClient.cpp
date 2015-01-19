// Qt
#include <QtNetwork/QTcpSocket>
// Hb
#include <HbLogService.h>
// Local
#include <com/tcp/HbTcpClient.h>
#include <com/tcp/HbTcpSocket.h>

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
    if( setConfiguration( config ) )
    {
        return HbAbstractClient::join();
    }

    return false;
}


bool HbTcpClient::setConfiguration( const HbTcpConfig & config )
{
    if( _socket )
    {
        HbError( "Can not apply configuration on instanciated socket." );
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
	q_assert_ptr( _socket );
	if( !_socket->connectToHost( this->configuration( ) ) )
    {
        HbError( "Can not connect to host." );
        return false;
    }

    return true;
}

bool HbTcpClient::disconnectFromNetwork()
{
	q_assert_ptr( _socket );
	if( !_socket->disconnectFromHost() )
	{
        HbError( "Can not disconnect from host." );
	}
    else
    {
        deleteSocket();
    }

    return ( !_socket );
}

void HbTcpClient::deleteSocket()
{
    _socket->disconnect();
    _socket->deleteLater();
    _socket = nullptr;
}


HbAbstractSocket * HbTcpClient::pendingConnection()
{
    if( _socket )
    {
        return _socket;
    }

    QTcpSocket * device = q_check_ptr( new QTcpSocket( this ) );
    _socket = q_check_ptr( new HbTcpSocket( device ) );

    connect( _socket, &HbAbstractSocket::socketError,
             this,    [this](){ emit socketError( _socket->error(), _socket->errorString() ); } );

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