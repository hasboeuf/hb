// Hb
#include <HbLogService.h>
// Local
#include <config/HbTcpConfig.h>
#include <contract/HbConnectionContract.h>


HbTcpConfig::HbTcpConfig() :
    HbNetworkConfig()
{
	setTimeout(timeout());

    mAddress = QHostAddress::Null;
    mPort = 0;
    mOptions = SocketOption::NoOptions;

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

        mAddress = config.mAddress;
        mPort    = config.mPort;
        mOptions = config.mOptions;
	}
}


HbTcpConfig & HbTcpConfig::operator =(const HbTcpConfig & config)
{
    if (this != &config)
	{
		HbNetworkConfig::operator =(config);
        setTimeout( timeout() );

        mAddress = config.mAddress;
        mPort    = config.mPort;
        mOptions = config.mOptions;
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
    mAddress = address;
}

void HbTcpConfig::setPort(quint16 port)
{
    mPort = port;
}


const QHostAddress & HbTcpConfig::address() const
{
    return mAddress;
}

quint16 HbTcpConfig::port() const
{
    return mPort;
}


void HbTcpConfig::setOptions(SocketOptions options)
{
    mOptions = options;
}

HbTcpConfig::SocketOptions HbTcpConfig::options() const
{
    return mOptions;
}

bool HbTcpConfig::isValid() const
{
	if (!HbNetworkConfig::isValid())
	{
		return false;
	}

    if (mAddress.isNull())
	{
		HbError("Null address.");
		return false;
	}

	return true;
}
