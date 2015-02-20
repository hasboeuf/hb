// Hb
#include <HbLogService.h>
// Local
#include <config/HbServerConfig.h>

HbServerConfig::HbServerConfig( ) :
    HbComConfig()
{
    mMaxUsersPerThread = 0; // Not threaded.
}

HbServerConfig::HbServerConfig( const HbServerConfig & config ) :
    HbComConfig( config )
{
    if (this != &config)
    {
        mMaxUsersPerThread = config.mMaxUsersPerThread;
    }
}


HbServerConfig & HbServerConfig::operator =( const HbServerConfig & config )
{
    if (this != &config)
    {
        HbComConfig::operator=( config );
        mMaxUsersPerThread = config.mMaxUsersPerThread;
    }

    return *this;
}

bool HbServerConfig::isValid() const
{
    return HbComConfig::isValid();
}

void HbServerConfig::setMaxUsersPerThread( quint16 max_users )
{
    mMaxUsersPerThread = max_users;
}

quint16 HbServerConfig::maxUsersPerThread() const
{
    return mMaxUsersPerThread;
}

bool HbServerConfig::isThreaded() const
{
    return ( mMaxUsersPerThread > 0 );
}

