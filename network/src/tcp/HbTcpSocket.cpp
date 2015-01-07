// Qt
#include <QtNetwork/QTcpSocket>
// Local
#include <tcp/HbTcpSocket.h>

using namespace hb::network;


HbTcpSocket::HbTcpSocket(QTcpSocket * device) :
	HbAbstractSocket(device)
{
	_device = device;
	_state = _device->state();

	connect(_device.data(), &QTcpSocket::connected, this, &HbAbstractSocket::connected,
		static_cast< Qt::ConnectionType >(Qt::DirectConnection | Qt::UniqueConnection));

	connect(_device.data(), &QTcpSocket::disconnected, this, &HbAbstractSocket::disconnected,
		static_cast< Qt::ConnectionType >(Qt::DirectConnection | Qt::UniqueConnection));

	connect(_device.data(), (void (QTcpSocket::*)(QAbstractSocket::SocketState)) &QTcpSocket::stateChanged,
        this, (void (HbTcpSocket::*)(QAbstractSocket::SocketState)) &HbTcpSocket::onStateChanged,
		static_cast< Qt::ConnectionType >(Qt::DirectConnection | Qt::UniqueConnection));

	connect(_device.data(), (void (QTcpSocket::*)(QAbstractSocket::SocketError)) &QTcpSocket::error,
        this, &HbTcpSocket::onError, Qt::UniqueConnection);
}

HbTcpSocket::~HbTcpSocket()
{
    if ( !_device.isNull() )
    {
		_device->abort();
    }
}


HbAbstractSocket::SocketType HbTcpSocket::type() const
{
	return TcpSocket;
}


bool HbTcpSocket::connectToHost(const HbTcpConfig & config)
{
	if (_state == QAbstractSocket::UnconnectedState)
	{
		_config = config;
		_device->connectToHost(_config.address(), _config.port(), QIODevice::ReadWrite);

		if (!_device->waitForConnected(_config.timeout().connection))
		{
			setErrorString(_device->error());
			return false;
		}
	}

	return true;
}

bool HbTcpSocket::disconnectFromHost()
{
	if (_state != QAbstractSocket::UnconnectedState)
	{
		_device->disconnectFromHost();

		if (_state != QAbstractSocket::UnconnectedState)
        {
            if (!_device->waitForDisconnected(_config.timeout().disconnection))
            {
                setErrorString(_device->error());
                return false;
            }
        }
	}

	return true;
}


bool HbTcpSocket::isListening() const
{
    return ( _state == QAbstractSocket::ConnectedState );
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

QAbstractSocket::SocketState HbTcpSocket::onStateChanged() const
{
	return _state;
}


void HbTcpSocket::onReadyRead()
{
    QDataStream stream( _device );

    if ( readStream(stream) < 0 )
    {
        onError(QAbstractSocket::UnknownSocketError);
    }
}


void HbTcpSocket::onError(QAbstractSocket::SocketError error)
{
	if (sender() == _device)
    {
		setErrorString(error);
    }

    emit this->error(error);
}

void HbTcpSocket::socketState(QAbstractSocket::SocketState state)
{
    if (_state == state)
	{
        return;
    }

    _state = state;
    if ( _state == QAbstractSocket::ClosingState )
    {
        _device->abort();
    }

}
