// Local
#include <config/service/auth/HbServiceAuthClientConfig.h>

using namespace hb::network;


HbServiceAuthClientConfig::HbServiceAuthClientConfig() :
    HbServiceAuthConfig()
{

}

HbServiceAuthClientConfig::HbServiceAuthClientConfig(const HbServiceAuthClientConfig & config) :
    HbServiceAuthConfig( config )
{
    if (this != &config)
    {

    }
}


HbServiceAuthClientConfig & HbServiceAuthClientConfig::operator =(const HbServiceAuthClientConfig & config)
{
    if (this != &config)
    {
        HbServiceAuthConfig::operator =( config );

    }

    return *this;
}

bool HbServiceAuthClientConfig::isValid() const
{
    if( HbServiceAuthConfig::isValid() )
    {
        return mFacebookAuthConfig.isValid();
    }

    return false;
}

void HbServiceAuthClientConfig::enableFacebookAuth( const hb::link::HbO2ClientConfig & config )
{
    mFacebookAuthConfig = config;
}

const hb::link::HbO2ClientConfig & HbServiceAuthClientConfig::facebookAuthConfig() const
{
    return mFacebookAuthConfig;
}

void HbServiceAuthClientConfig::enableGoogleAuth( const hb::link::HbO2ClientConfig & config )
{
    mGoogleAuthConfig = config;
}

const hb::link::HbO2ClientConfig & HbServiceAuthClientConfig::googleAuthConfig() const
{
    return mGoogleAuthConfig;
}
