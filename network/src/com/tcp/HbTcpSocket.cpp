// Qt
#include <QtNetwork/QTcpSocket>
// Hb
#include <HbLogService.h>
// Local
#include <com/tcp/HbTcpSocket.h>

using namespace hb::network;


HbTcpSocket::HbTcpSocket( QTcpSocket * device ) :
    HbAbstractSocket( device )
{
    q_assert_ptr( device );
	_device = device;

    connect( _device, &QTcpSocket::stateChanged, this, &HbTcpSocket::onStateChanged );
    connect( _device, ( void (QTcpSocket::*)( QAbstractSocket::SocketError ) ) &QTcpSocket::error,
    [this]()
    {
        emit socketError();
    } );
}

HbTcpSocket::~HbTcpSocket()
{
    // HbAbstractSocket handles the destruction.
}


HbAbstractSocket::SocketType HbTcpSocket::type() const
{
	return TcpSocket;
}


bool HbTcpSocket::connectToHost(const HbTcpConfig & config)
{
    if ( state() == QAbstractSocket::UnconnectedState)
	{
		_config = config;
        _device->connectToHost( _config.address(), _config.port(), QIODevice::ReadWrite );

        return true;
    }

    return false;
}

bool HbTcpSocket::disconnectFromHost()
{
    if ( state() != QAbstractSocket::UnconnectedState)
	{
		_device->disconnectFromHost();
        return true;
	}

    return false;
}


bool HbTcpSocket::isListening() const
{
    return ( state() == QAbstractSocket::ConnectedState );
}


void HbTcpSocket::setSocketOption(QAbstractSocket::SocketOption option, bool enable)
{
	switch (option)
	{
	case QAbstractSocket::LowDelayOption:
	case QAbstractSocket::KeepAliveOption:
	case QAbstractSocket::MulticastLoopbackOption:

		_device->setSocketOption(option, enable);
		break;

	default:

		Q_UNREACHABLE();
		break;
	}
}

bool HbTcpSocket::socketOption(QAbstractSocket::SocketOption option) const
{
	switch (option)
	{
	case QAbstractSocket::LowDelayOption:
	case QAbstractSocket::KeepAliveOption:
	case QAbstractSocket::MulticastLoopbackOption:
		return _device->socketOption(option).toBool();

	default:
		return false;
	}
}


QAbstractSocket::SocketError HbTcpSocket::error() const
{
	return _device->error();
}

QAbstractSocket::SocketState HbTcpSocket::state() const
{
    return _device->state();
}


void HbTcpSocket::onReadyRead()
{
    QDataStream stream( _device );

    if ( readStream(stream) < 0 )
    {
        HbError( "Read stream failed." );
    }
}

void HbTcpSocket::onStateChanged( QAbstractSocket::SocketState state )
{
    q_assert( _device == sender() );

    if( state == QAbstractSocket::UnconnectedState )
    {
        HbInfo( "Socket enters UnconnectedState." );
        emit socketDisconnected();
    }
    else if( state == QAbstractSocket::HostLookupState )
    {
        HbInfo( "Socket enters HostLookupState." );
    }
    else if( state == QAbstractSocket::ConnectingState )
    {
        HbInfo( "Socket enters ConnectingState." );
    }
    else if( state == QAbstractSocket::ConnectedState )
    {
        HbInfo( "Socket enters ConnectedState." );
        emit socketConnected();
    }
    else if( state == QAbstractSocket::BoundState )
    {
        HbInfo( "Socket enters BoundState." );
    }
    else if( state == QAbstractSocket::ClosingState )
    {
        HbInfo( "Socket enters ClosingState." );
    }
    else if( state == QAbstractSocket::ListeningState )
    {
        HbInfo( "Socket enters ListeningState." );
    }

    emit socketStateChanged();
}
