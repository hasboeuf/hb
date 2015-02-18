// Local
#include <config/service/presence/HbServicePresenceClientConfig.h>

using namespace hb::network;


HbServicePresenceClientConfig::HbServicePresenceClientConfig() :
    HbServicePresenceConfig()
{

}

HbServicePresenceClientConfig::HbServicePresenceClientConfig(const HbServicePresenceClientConfig & config) :
    HbServicePresenceConfig( config )
{
    if (this != &config)
    {

    }
}


HbServicePresenceClientConfig & HbServicePresenceClientConfig::operator =(const HbServicePresenceClientConfig & config)
{
    if (this != &config)
    {
        HbServicePresenceConfig::operator =( config );

    }

    return *this;
}

bool HbServicePresenceClientConfig::isValid() const
{
    return HbServicePresenceConfig::isValid();
}
