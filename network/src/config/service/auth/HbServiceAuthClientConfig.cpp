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
    return HbServiceAuthConfig::isValid();
}
