// Hb
#include <HbLogService.h>
// Local
#include <config/com/HbServerConfig.h>

HbServerConfig::HbServerConfig( ) :
    HbNetworkConfig()
{
	mMaxUsersPerThread = 0; // Not threaded.
}

HbServerConfig::HbServerConfig( const HbServerConfig & config ) :
	HbNetworkConfig( config )
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
		HbNetworkConfig::operator=( config );
		mMaxUsersPerThread = config.mMaxUsersPerThread;
	}

	return *this;
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

const HbTimeoutServerConfig & HbServerConfig::timeout() const
{
    return mTimeout;
}

void HbServerConfig::setTimeout( const HbTimeoutServerConfig & timeout )
{
    mTimeout = timeout;
}

bool HbServerConfig::isValid() const
{
	return HbNetworkConfig::isValid();
}
