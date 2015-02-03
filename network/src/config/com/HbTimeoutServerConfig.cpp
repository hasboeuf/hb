// Local
#include <config/com/HbTimeoutServerConfig.h>

HbTimeoutServerConfig::HbTimeoutServerConfig() :
    HbTimeoutConfig()
{
    mWarningThreshold = 0;
    mKickThreshold    = 0;
}

HbTimeoutServerConfig::HbTimeoutServerConfig( const HbTimeoutServerConfig & config ) :
    HbTimeoutConfig( config )
{
    if( &config != this )
    {
        mWarningThreshold = config.mWarningThreshold;
        mKickThreshold    = config.mKickThreshold;
    }
}

HbTimeoutServerConfig & HbTimeoutServerConfig::operator =( const HbTimeoutServerConfig & config )
{
    if( &config != this )
    {
        HbTimeoutConfig::operator =( config );
        mWarningThreshold = config.mWarningThreshold;
        mKickThreshold    = config.mKickThreshold;
    }
    return ( *this );
}

void HbTimeoutServerConfig::setWarningThreshold( quint16 duration )
{
    mWarningThreshold = duration;
}
quint16 HbTimeoutServerConfig::warningThreshold() const
{
    return mWarningThreshold;
}

void HbTimeoutServerConfig::setKickThreshold( quint16 duration )
{
    mKickThreshold = duration;
}
quint16 HbTimeoutServerConfig::kickThreshold() const
{
    return mKickThreshold;
}

bool HbTimeoutServerConfig::isValid() const
{
    if( isTimeoutEnabled() )
    {
        if( ( mWarningThreshold <= tickInterval() ) ||
            ( mKickThreshold <= mWarningThreshold ) )
        {
            return false;
        }
    }

    return true;
}
