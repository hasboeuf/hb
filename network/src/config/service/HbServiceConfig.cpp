// Local
#include <config/service/HbServiceConfig.h>

using namespace hb::network;


HbServiceConfig::HbServiceConfig()
{

}

HbServiceConfig::HbServiceConfig(const HbServiceConfig & config)
{
    if (this != &config)
    {

    }
}


HbServiceConfig & HbServiceConfig::operator =(const HbServiceConfig & config)
{
    if (this != &config)
    {

    }

    return *this;
}

bool HbServiceConfig::isValid() const
{
    return true;
}
