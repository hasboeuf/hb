// Local
#include <config/HbClientConfig.h>

HbClientConfig::HbClientConfig( const HbClientConfig & config ) :
    HbNetworkConfig( config )
{
    if( &config != this )
    {
        mTimeout = config.mTimeout;
    }
}

HbClientConfig & HbClientConfig::operator =( const HbClientConfig & config )
{
    if( &config != this )
    {
        mTimeout = config.mTimeout;
    }
    return ( *this);
}

const HbTimeoutClientConfig & HbClientConfig::timeout() const
{
    return mTimeout;
}

void HbClientConfig::setTimeout( const HbTimeoutClientConfig & timeout )
{
    mTimeout = timeout;
}

bool HbClientConfig::isValid() const
{
    if( HbNetworkConfig::isValid() )
    {
        return mTimeout.isValid();
    }

    return false;
}
