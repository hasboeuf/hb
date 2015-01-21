// Local
#include <config/HbNetworkConfig.h>

using namespace hb::network;


HbNetworkConfig::HbNetworkConfig()
{
    mTimeout.connection = -1;
    mTimeout.reconnection = 1000;
    mTimeout.disconnection = -1;
    mOpenMode = QIODevice::ReadWrite;
}

HbNetworkConfig::HbNetworkConfig(const HbNetworkConfig & config)
{
	if (this != &config)
	{
        mTimeout = config.mTimeout;
        mOpenMode = config.mOpenMode;
        mExchanges = config.mExchanges;
	}
}


HbNetworkConfig & HbNetworkConfig::operator =(const HbNetworkConfig & config)
{
	if (this != &config)
	{
        mTimeout = config.mTimeout;
        mOpenMode = config.mOpenMode;
        mExchanges = config.mExchanges;
	}

	return *this;
}

void HbNetworkConfig::setOwner(quint16 address)
{
    mUuid = address;
}

quint16 HbNetworkConfig::owner( ) const
{
    return mUuid;
}


void HbNetworkConfig::setTimeout(const Timeout & timeout)
{
    mTimeout.connection    = qMax< qint16 >(-1, timeout.connection   );
    mTimeout.reconnection  = qMax< qint16 >(-1, timeout.reconnection );
    mTimeout.disconnection = qMax< qint16 >(-1, timeout.disconnection);
}

void HbNetworkConfig::setOpenMode(QIODevice::OpenMode mode)
{
    if (mOpenMode != mode)
	{
		switch (mode)
		{
		case QIODevice::ReadOnly:
		case QIODevice::WriteOnly:
		case QIODevice::ReadWrite:

            mOpenMode = mode;
			break;

		case QIODevice::Append:
		case QIODevice::Truncate:

            mOpenMode = QIODevice::WriteOnly;
			break;

		default:

            mOpenMode = QIODevice::NotOpen;
			break;
		}
	}
}

const HbNetworkConfig::Timeout & HbNetworkConfig::timeout() const
{
    return mTimeout;
}

QIODevice::OpenMode HbNetworkConfig::openMode() const
{
    return mOpenMode;
}

int HbNetworkConfig::uuid() const
{
    return mUuid;
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
    return ( mOpenMode != QIODevice::NotOpen );
}
