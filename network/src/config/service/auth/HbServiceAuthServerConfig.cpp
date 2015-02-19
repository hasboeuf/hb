// Hb
#include <HbLogService.h>
// Local
#include <config/service/auth/HbServiceAuthServerConfig.h>

using namespace hb::network;


HbServiceAuthServerConfig::HbServiceAuthServerConfig() :
    HbServiceAuthConfig()
{
    mAuthMaxTries = 0;
    mAuthTimeout  = 0;
}

HbServiceAuthServerConfig::HbServiceAuthServerConfig(const HbServiceAuthServerConfig & config) :
    HbServiceAuthConfig( config )
{
    if (this != &config)
    {
        HbServiceAuthConfig::operator =( config );

        mAuthMaxTries = config.mAuthMaxTries;
        mAuthTimeout  = config.mAuthTimeout;
    }
}


HbServiceAuthServerConfig & HbServiceAuthServerConfig::operator =(const HbServiceAuthServerConfig & config)
{
    if (this != &config)
    {
        HbServiceAuthConfig::operator =( config );
        mAuthMaxTries = config.mAuthMaxTries;
        mAuthTimeout  = config.mAuthTimeout;
    }

    return *this;
}

bool HbServiceAuthServerConfig::isValid() const
{
    if( !HbServiceAuthConfig::isValid() )
    {
        return false;
    }

    if( mAuthMaxTries < 1 )
    {
        HbError( "AuthMaxTries must be > 0." );
        return false;
    }

    if( mAuthTimeout < 1 )
    {
        HbError( "mAuthTimeout must be > 0 second.");
        return false;
    }

    return true;
}

void HbServiceAuthServerConfig::setAuthMaxTries( quint16 max )
{
    mAuthMaxTries = max;
}

quint16 HbServiceAuthServerConfig::authMaxTries() const
{
    return mAuthMaxTries;
}

void HbServiceAuthServerConfig::setAuthTimeout( quint16 timeout )
{
    mAuthTimeout = timeout;
}

quint16 HbServiceAuthServerConfig::authTimeout() const
{
    return mAuthTimeout;
}
