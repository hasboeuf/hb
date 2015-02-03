// Hb
#include <HbLogService.h>
// Local
#include <config/com/HbTcpConfig.h>
#include <contract/HbConnectionContract.h>
#include <contract/HbNetworkHeader.h>

using namespace hb::network;

HbTcpConfig::HbTcpConfig() :
    HbNetworkConfig()
{
    mAddress = QHostAddress::Null;
    mPort = 0;
    mOptions = SocketOption::NoOptions;

    mExchanges.plug< HbConnectionContract >();
}

HbTcpConfig::HbTcpConfig(const HbTcpConfig & config) :
	HbNetworkConfig(config)
{
	if (this != &config)
	{
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

        mAddress = config.mAddress;
        mPort    = config.mPort;
        mOptions = config.mOptions;
	}

    return ( *this );
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
