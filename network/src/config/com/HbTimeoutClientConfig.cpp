// Local
#include <config/com/HbTimeoutClientConfig.h>

HbTimeoutClientConfig::HbTimeoutClientConfig() :
    HbTimeoutConfig()
{
    mReconnectionDelay = 0;
}

HbTimeoutClientConfig::HbTimeoutClientConfig(const HbTimeoutClientConfig & config) :
    HbTimeoutConfig( config )
{
    if( &config != this )
    {
        mReconnectionDelay = config.mReconnectionDelay;
    }
}

HbTimeoutClientConfig & HbTimeoutClientConfig::operator =(const HbTimeoutClientConfig & config)
{
    if( &config != this )
    {
        mReconnectionDelay = config.mReconnectionDelay;
    }
    return ( * this );
}

void HbTimeoutClientConfig::setReconnectionDelay( quint16 duration )
{
    mReconnectionDelay = duration;
}

quint16 HbTimeoutClientConfig::reconnectionDelay() const
{
    return mReconnectionDelay;
}

bool HbTimeoutClientConfig::isValid() const
{
    return true;
}
