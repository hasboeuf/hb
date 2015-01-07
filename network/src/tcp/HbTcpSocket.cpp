// Qt
#include <QtNetwork/QTcpSocket>
// Hb
#include <HbLogService.h>
// Local
#include <tcp/HbTcpSocket.h>

using namespace hb::network;


HbTcpSocket::HbTcpSocket(QTcpSocket * device) :
	HbAbstractSocket(device)
{
    q_assert_ptr( device );
	_device = device;

    connect(_device, &QTcpSocket::connected,    this, &HbAbstractSocket::socketConnected,    Qt::UniqueConnection);
    connect(_device, &QTcpSocket::disconnected, this, &HbAbstractSocket::socketDisconnected, Qt::UniqueConnection);
    connect(_device, &QTcpSocket::stateChanged,
    [this](QAbstractSocket::SocketState state)
    {
        HbError( "Socket state changed [%d]", state );
        emit socketStateChanged();
    } );
    connect(_device, ( void (QTcpSocket::*)( QAbstractSocket::SocketError ) ) &QTcpSocket::error,
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
		_device->connectToHost(_config.address(), _config.port(), QIODevice::ReadWrite);

        if ( !_device->waitForConnected(_config.timeout().connection))
		{
			return false;
		}
	}

	return true;
}

bool HbTcpSocket::disconnectFromHost()
{
    if ( state() != QAbstractSocket::UnconnectedState)
	{
		_device->disconnectFromHost();

        if ( state() != QAbstractSocket::UnconnectedState )
        {
            if ( !_device->waitForDisconnected(_config.timeout().disconnection) )
            {
                return false;
            }
        }
	}

	return true;
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
