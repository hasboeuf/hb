// Local
#include <config/com/HbNetworkConfig.h>

using namespace hb::network;


HbNetworkConfig::HbNetworkConfig()
{
    mOpenMode = QIODevice::ReadWrite;
}

HbNetworkConfig::HbNetworkConfig(const HbNetworkConfig & config)
{
	if (this != &config)
	{
        mOpenMode = config.mOpenMode;
        mExchanges = config.mExchanges;
	}
}


HbNetworkConfig & HbNetworkConfig::operator =(const HbNetworkConfig & config)
{
	if (this != &config)
	{
        mOpenMode = config.mOpenMode;
        mExchanges = config.mExchanges;
	}

	return *this;
}

bool HbNetworkConfig::isValid() const
{
    return ( mOpenMode != QIODevice::NotOpen );
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

QIODevice::OpenMode HbNetworkConfig::openMode() const
{
    return mOpenMode;
}

const HbNetworkExchanges & HbNetworkConfig::exchanges() const
{
    return mExchanges;
}

HbNetworkExchanges & HbNetworkConfig::exchanges()
{
    return mExchanges;
}
