// Local
#include <config/HbClientConfig.h>

HbClientConfig::HbClientConfig() :
    HbComConfig()
{
    mReconnectionDelay = 0;
}

HbClientConfig::HbClientConfig( const HbClientConfig & config ) :
    HbComConfig( config )
{
    if( &config != this )
    {
        mReconnectionDelay = config.mReconnectionDelay;
    }
}

HbClientConfig & HbClientConfig::operator =( const HbClientConfig & config )
{
    if( &config != this )
    {
        HbComConfig::operator =( config );

        mReconnectionDelay = config.mReconnectionDelay;
    }
    return ( *this);
}

bool HbClientConfig::isValid() const
{
    if( !HbComConfig::isValid() )
    {
        return false;
    }

    return true;
}

void HbClientConfig::setReconnectionDelay( quint16 duration )
{
    mReconnectionDelay = duration;
}

quint16 HbClientConfig::reconnectionDelay() const
{
    return mReconnectionDelay;
}
