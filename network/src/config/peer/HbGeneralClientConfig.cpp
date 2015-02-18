// Local
#include <config/peer/HbGeneralClientConfig.h>

using namespace hb::network;


HbGeneralClientConfig::HbGeneralClientConfig(const HbGeneralClientConfig & config) :
    HbGeneralConfig( config )
{
    if (this != &config)
    {
        mAuthConfig     = config.mAuthConfig;
        mChannelConfig  = config.mChannelConfig;
        mPresenceConfig = config.mPresenceConfig;

    }
}


HbGeneralClientConfig & HbGeneralClientConfig::operator =(const HbGeneralClientConfig & config)
{
    if (this != &config)
    {
        HbGeneralConfig::operator=( config );

        mAuthConfig     = config.mAuthConfig;
        mChannelConfig  = config.mChannelConfig;
        mPresenceConfig = config.mPresenceConfig;
    }

    return *this;
}


bool HbGeneralClientConfig::isValid() const
{
    if( HbGeneralConfig::isValid() )
    {
        // TODO complete
        return true;
    }
    return false;
}

HbServiceAuthClientConfig & HbGeneralClientConfig::auth()
{
    return mAuthConfig;
}

HbServiceChannelClientConfig & HbGeneralClientConfig::channel()
{
    return mChannelConfig;
}

HbServicePresenceClientConfig & HbGeneralClientConfig::presence()
{
    return mPresenceConfig;
}
