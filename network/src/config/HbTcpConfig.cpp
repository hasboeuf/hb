// Hb
#include <HbLogService.h>
// Local
#include <config/HbTcpConfig.h>
#include <contract/HbConnectionContract.h>


HbTcpConfig::HbTcpConfig() :
    HbNetworkConfig()
{
	setTimeout(timeout());

	_address = QHostAddress::Null;
	_port = 0;
	_options = SocketOption::NoOptions;

    mExchanges.plug< HbConnectionContract >();

    if( mExchanges.registered( HbNetworkProtocol::SERVICE_AUTH, HbNetworkProtocol::CODE_CONNECTION_REQUEST ) )
    {
        QString toto;
        HbNetworkContract * c = mExchanges.contract( HbNetworkProtocol::SERVICE_AUTH, HbNetworkProtocol::CODE_CONNECTION_REQUEST );
        HbConnectionContract * cc = dynamic_cast< HbConnectionContract * >( c );
        QString tata;
    }
}

HbTcpConfig::HbTcpConfig(const HbTcpConfig & config) :
	HbNetworkConfig(config)
{
	if (this != &config)
	{
		setTimeout(timeout());

		_address = config._address;
		_port    = config._port;
		_options = config._options;
	}
}


HbTcpConfig & HbTcpConfig::operator =(const HbTcpConfig & config)
{
    if (this != &config)
	{
		HbNetworkConfig::operator =(config);
        setTimeout( timeout() );

		_address = config._address;
		_port    = config._port;
		_options = config._options;
	}

	return *this;
}


void HbTcpConfig::setTimeout(const Timeout & timeout)
{
	Timeout updated = timeout;
	HbNetworkConfig::setTimeout(updated);

	updated.connection = qMax< qint16 >(10, updated.connection);
}


void HbTcpConfig::setAddress(const QString & address)
{
	setAddress(QHostAddress(address));
}

void HbTcpConfig::setAddress(const QHostAddress & address)
{
	_address = address;
}

void HbTcpConfig::setPort(quint16 port)
{
	_port = port;
}


const QHostAddress & HbTcpConfig::address() const
{
	return _address;
}

quint16 HbTcpConfig::port() const
{
	return _port;
}


void HbTcpConfig::setOptions(SocketOptions options)
{
	_options = options;
}

HbTcpConfig::SocketOptions HbTcpConfig::options() const
{
	return _options;
}

bool HbTcpConfig::isValid() const
{
	if (!HbNetworkConfig::isValid())
	{
		return false;
	}

	if (_address.isNull())
	{
		HbError("Null address.");
		return false;
	}

	return true;
}
