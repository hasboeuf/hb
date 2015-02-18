// Local
#include <config/service/auth/HbServiceAuthConfig.h>

using namespace hb::network;


HbServiceAuthConfig::HbServiceAuthConfig() :
    HbServiceConfig()
{

}

HbServiceAuthConfig::HbServiceAuthConfig(const HbServiceAuthConfig & config) :
    HbServiceConfig( config )
{
	if (this != &config)
	{

	}
}


HbServiceAuthConfig & HbServiceAuthConfig::operator =(const HbServiceAuthConfig & config)
{
	if (this != &config)
	{
        HbServiceConfig::operator =( config );

	}

	return *this;
}

bool HbServiceAuthConfig::isValid() const
{
    return HbServiceConfig::isValid();
}
