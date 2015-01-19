// Local
#include <config/HbNetworkConfig.h>
#include <contract/HbConnectionContract.h>

using namespace hb::network;


HbNetworkConfig::HbNetworkConfig()
{
	_timeout.connection = -1;
	_timeout.reconnection = 1000;
	_timeout.disconnection = -1;

	_openMode = QIODevice::ReadWrite;

    mExchanges.plug< HbConnectionContract >();
}

HbNetworkConfig::HbNetworkConfig(const HbNetworkConfig & config)
{
	if (this != &config)
	{
		_timeout = config._timeout;
		_openMode = config._openMode;
        mExchanges = config.mExchanges;
	}
}


HbNetworkConfig & HbNetworkConfig::operator =(const HbNetworkConfig & config)
{
	if (this != &config)
	{
		_timeout = config._timeout;
		_openMode = config._openMode;
        mExchanges = config.mExchanges;
	}

	return *this;
}

void HbNetworkConfig::setOwner(quint16 address)
{
	_uuid = address;
}

quint16 HbNetworkConfig::owner( ) const
{
	return _uuid;
}


void HbNetworkConfig::setTimeout(const Timeout & timeout)
{
	_timeout.connection    = qMax< qint16 >(-1, timeout.connection   );
	_timeout.reconnection  = qMax< qint16 >(-1, timeout.reconnection );
	_timeout.disconnection = qMax< qint16 >(-1, timeout.disconnection);
}

void HbNetworkConfig::setOpenMode(QIODevice::OpenMode mode)
{
	if (_openMode != mode)
	{
		switch (mode)
		{
		case QIODevice::ReadOnly:
		case QIODevice::WriteOnly:
		case QIODevice::ReadWrite:

			_openMode = mode;
			break;

		case QIODevice::Append:
		case QIODevice::Truncate:

			_openMode = QIODevice::WriteOnly;
			break;

		default:

			_openMode = QIODevice::NotOpen;
			break;
		}
	}
}

const HbNetworkConfig::Timeout & HbNetworkConfig::timeout() const
{
	return _timeout;
}

QIODevice::OpenMode HbNetworkConfig::openMode() const
{
	return _openMode;
}

int HbNetworkConfig::uuid() const
{
	return _uuid;
}

const HbNetworkExchanges & HbNetworkConfig::exchanges() const
{
    return mExchanges;
}

HbNetworkExchanges & HbNetworkConfig::exchanges()
{
    return mExchanges;
}

bool HbNetworkConfig::isValid() const
{
	return (_openMode != QIODevice::NotOpen);
}