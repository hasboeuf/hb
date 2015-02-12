// Local
#include <config/peer/HbGeneralServerConfig.h>

using namespace hb::network;


HbGeneralServerConfig::HbGeneralServerConfig(const HbGeneralServerConfig & config) :
    HbGeneralConfig( config )
{
	if (this != &config)
	{

	}
}


HbGeneralServerConfig & HbGeneralServerConfig::operator =(const HbGeneralServerConfig & config)
{
	if (this != &config)
	{

	}

	return *this;
}


bool HbGeneralServerConfig::isValid() const
{
    if( HbGeneralConfig::isValid() )
    {
        // TODO check channel.
        return true;
    }
    return false;
}
