// Local
#include <config/com/HbNetworkConfig.h>

using namespace hb::network;


HbNetworkConfig::HbNetworkConfig()
{
    mOpenMode = QIODevice::ReadWrite;
    mBadHeaderTolerant = true;
}

HbNetworkConfig::HbNetworkConfig( const HbNetworkConfig & config )
{
    if ( this != &config )
    {
        mOpenMode = config.mOpenMode;
        mBadHeaderTolerant = config.mBadHeaderTolerant;
        mExchanges = config.mExchanges;
    }
}


HbNetworkConfig & HbNetworkConfig::operator =( const HbNetworkConfig & config )
{
    if ( this != &config )
    {
        mOpenMode = config.mOpenMode;
        mBadHeaderTolerant = config.mBadHeaderTolerant;
        mExchanges = config.mExchanges;
    }

    return *this;
}

bool HbNetworkConfig::isValid() const
{
    return ( mOpenMode != QIODevice::NotOpen );
}

void HbNetworkConfig::setOpenMode( QIODevice::OpenMode mode )
{
    if ( mOpenMode != mode )
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

void HbNetworkConfig::setBadHeaderTolerant( bool tolerant )
{
    mBadHeaderTolerant = tolerant;
}

bool HbNetworkConfig::isBadHeaderTolerant() const
{
    return mBadHeaderTolerant;
}

const HbNetworkExchanges & HbNetworkConfig::exchanges() const
{
    return mExchanges;
}

HbNetworkExchanges & HbNetworkConfig::exchanges()
{
    return mExchanges;
}
