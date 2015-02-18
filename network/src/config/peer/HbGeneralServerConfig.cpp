// Local
#include <config/peer/HbGeneralServerConfig.h>

using namespace hb::network;


HbGeneralServerConfig::HbGeneralServerConfig(const HbGeneralServerConfig & config) :
    HbGeneralConfig( config )
{
	if (this != &config)
	{
        mAuthConfig     = config.mAuthConfig;
        mChannelConfig  = config.mChannelConfig;
        mPresenceConfig = config.mPresenceConfig;
	}
}


HbGeneralServerConfig & HbGeneralServerConfig::operator =(const HbGeneralServerConfig & config)
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


bool HbGeneralServerConfig::isValid() const
{
    if( HbGeneralConfig::isValid() )
    {
        // TODO complete
        return true;
    }
    return false;
}

HbServiceAuthServerConfig & HbGeneralServerConfig::auth()
{
    return mAuthConfig;
}

HbServiceChannelServerConfig & HbGeneralServerConfig::channel()
{
    return mChannelConfig;
}

HbServicePresenceServerConfig & HbGeneralServerConfig::presence()
{
    return mPresenceConfig;
}
