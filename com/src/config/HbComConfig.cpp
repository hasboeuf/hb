// Local
#include <config/HbComConfig.h>

using namespace hb::com;


HbComConfig::HbComConfig()
{
    mOpenMode = QIODevice::ReadWrite;
}

HbComConfig::HbComConfig( const HbComConfig & config )
{
    if ( this != &config )
    {
        mOpenMode = config.mOpenMode;
        mExchanges = config.mExchanges;
    }
}


HbComConfig & HbComConfig::operator =( const HbComConfig & config )
{
    if ( this != &config )
    {
        mOpenMode = config.mOpenMode;
        mExchanges = config.mExchanges;
    }

    return *this;
}

bool HbComConfig::isValid() const
{
    return ( mOpenMode != QIODevice::NotOpen );
}

void HbComConfig::setOpenMode( QIODevice::OpenMode mode )
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

QIODevice::OpenMode HbComConfig::openMode() const
{
    return mOpenMode;
}

const HbComExchanges & HbComConfig::exchanges() const
{
    return mExchanges;
}

HbComExchanges & HbComConfig::exchanges()
{
    return mExchanges;
}
