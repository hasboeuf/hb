// Hb
#include <HbLogService.h>
// Local
#include <config/service/presence/HbServicePresenceServerConfig.h>

using namespace hb::network;


HbServicePresenceServerConfig::HbServicePresenceServerConfig() :
    HbServicePresenceConfig()
{
    mWarningAliveThreshold = 0;
    mKickAliveThreshold    = 0;
}

HbServicePresenceServerConfig::HbServicePresenceServerConfig(const HbServicePresenceServerConfig & config) :
    HbServicePresenceConfig( config )
{
    if (this != &config)
    {
        mWarningAliveThreshold = config.mWarningAliveThreshold;
        mKickAliveThreshold    = config.mKickAliveThreshold;
    }
}


HbServicePresenceServerConfig & HbServicePresenceServerConfig::operator =(const HbServicePresenceServerConfig & config)
{
    if (this != &config)
    {
        HbServicePresenceConfig::operator =( config );

        mWarningAliveThreshold = config.mWarningAliveThreshold;
        mKickAliveThreshold    = config.mKickAliveThreshold;
    }

    return *this;
}

bool HbServicePresenceServerConfig::isValid() const
{
    if( !HbServicePresenceConfig::isValid() )
    {
        return false;
    }

    if( mWarningAliveThreshold <= 0 ||
        mKickAliveThreshold <= mWarningAliveThreshold )
    {
        qWarning() << "Must be 0 < WarningAliveThreshold < KickAliveThreshold";
        return false;
    }

    return true;
}

void HbServicePresenceServerConfig::setWarningAliveThreshold( quint16 threshold )
{
    mWarningAliveThreshold = threshold;
}

quint16 HbServicePresenceServerConfig::warningAliveThreshold() const
{
    return mWarningAliveThreshold;
}

void HbServicePresenceServerConfig::setKickAliveThreshold( quint16 threshold )
{
    mKickAliveThreshold = threshold;
}

quint16 HbServicePresenceServerConfig::kickAliveThreshold() const
{
    return mKickAliveThreshold;
}
