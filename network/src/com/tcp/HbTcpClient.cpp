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
    mpSocket = nullptr;
}

HbTcpClient::~HbTcpClient()
{
    leave();
}


bool HbTcpClient::join( const HbTcpClientConfig & config )
{
    if( setConfiguration( config ) )
    {
        return HbAbstractClient::join();
    }

    return false;
}

sockuid HbTcpClient::uid() const // TODO CHECK
{
    if( mpSocket )
    {
        return mpSocket->uid();
    }
    else
    {
        return 0;
    }
}


bool HbTcpClient::setConfiguration( const HbTcpClientConfig & config )
{
    if( mpSocket )
    {
        HbError( "Can not apply configuration on instanciated socket." );
        return false;
    }

    mConfig = config;
    return true;
}

const HbTcpClientConfig &HbTcpClient::configuration() const
{
    return mConfig;
}

bool HbTcpClient::connectToNetwork()
{
    q_assert_ptr( mpSocket );
    if( !mpSocket->connectToHost( this->configuration( ) ) )
    {
        HbError( "Can not connect to host." );
        return false;
    }

    return true;
}

bool HbTcpClient::disconnectFromNetwork()
{
    q_assert_ptr( mpSocket );
    if( !mpSocket->disconnectFromHost() )
	{
        HbError( "Can not disconnect from host." );
	}
    else
    {
        deleteSocket();
    }

    return ( !mpSocket );
}

void HbTcpClient::deleteSocket()
{
    mpSocket->disconnect();
    mpSocket->deleteLater();
    mpSocket = nullptr;
}


HbAbstractSocket * HbTcpClient::pendingConnection()
{
    if( mpSocket )
    {
        return mpSocket;
    }

    QTcpSocket * device = q_check_ptr( new QTcpSocket( this ) );
    mpSocket = q_check_ptr( new HbTcpSocket( device ) );

    connect( mpSocket, &HbAbstractSocket::socketError,
             this,    [this](){ emit socketError( mpSocket->error(), mpSocket->errorString() ); } );

    HbTcpConfig::SocketOptions options = mConfig.options();

    mpSocket->setSocketOption( QAbstractSocket::LowDelayOption, options.testFlag( HbTcpConfig::SocketOption::LowDelay ) );
    mpSocket->setSocketOption( QAbstractSocket::KeepAliveOption, options.testFlag( HbTcpConfig::SocketOption::KeepAlive ) );
    mpSocket->setSocketOption( QAbstractSocket::MulticastLoopbackOption, options.testFlag( HbTcpConfig::SocketOption::MulticastLoopback ) );

    return mpSocket;
}

HbAbstractSocket * HbTcpClient::currentConnection() const
{
    return mpSocket;
}
