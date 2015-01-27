// Local
#include <config/HbTimeoutConfig.h>

HbTimeoutConfig::HbTimeoutConfig()
{
    mTickInterval = 0;
}

HbTimeoutConfig::HbTimeoutConfig( const HbTimeoutConfig & config )
{
    if( &config != this )
    {
        mTickInterval = config.mTickInterval;
    }
}

HbTimeoutConfig & HbTimeoutConfig::operator =( const HbTimeoutConfig & config )
{
    if( &config != this )
    {
        mTickInterval = config.mTickInterval;
    }
    return ( * this );
}

void HbTimeoutConfig::setTickInterval( quint16 interval )
{
    mTickInterval = interval;
}

quint16 HbTimeoutConfig::tickInterval() const
{
    return mTickInterval;
}

bool HbTimeoutConfig::isTimeoutEnabled() const
{
    return ( mTickInterval > 0 );
}

bool HbTimeoutConfig::isValid() const
{
    return true;
}
