// Local
#include <config/service/auth/HbServiceAuthServerConfig.h>

using namespace hb::network;


HbServiceAuthServerConfig::HbServiceAuthServerConfig() :
    HbServiceAuthConfig()
{

}

HbServiceAuthServerConfig::HbServiceAuthServerConfig(const HbServiceAuthServerConfig & config) :
    HbServiceAuthConfig( config )
{
	if (this != &config)
	{

	}
}


HbServiceAuthServerConfig & HbServiceAuthServerConfig::operator =(const HbServiceAuthServerConfig & config)
{
	if (this != &config)
	{
        HbServiceAuthConfig::operator =( config );

	}

	return *this;
}

bool HbServiceAuthServerConfig::isValid() const
{
    return HbServiceAuthConfig::isValid();
}
