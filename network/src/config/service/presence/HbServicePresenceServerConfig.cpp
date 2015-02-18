// Local
#include <config/service/presence/HbServicePresenceServerConfig.h>

using namespace hb::network;


HbServicePresenceServerConfig::HbServicePresenceServerConfig() :
    HbServicePresenceConfig()
{

}

HbServicePresenceServerConfig::HbServicePresenceServerConfig(const HbServicePresenceServerConfig & config) :
    HbServicePresenceConfig( config )
{
    if (this != &config)
    {

    }
}


HbServicePresenceServerConfig & HbServicePresenceServerConfig::operator =(const HbServicePresenceServerConfig & config)
{
    if (this != &config)
    {
        HbServicePresenceConfig::operator =( config );

    }

    return *this;
}

bool HbServicePresenceServerConfig::isValid() const
{
    return HbServicePresenceConfig::isValid();
}
