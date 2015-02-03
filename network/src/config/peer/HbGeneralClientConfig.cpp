// Local
#include <config/peer/HbGeneralClientConfig.h>

using namespace hb::network;


HbGeneralClientConfig::HbGeneralClientConfig(const HbGeneralClientConfig & config) :
    HbGeneralConfig( config )
{
    if (this != &config)
    {

    }
}


HbGeneralClientConfig & HbGeneralClientConfig::operator =(const HbGeneralClientConfig & config)
{
    if (this != &config)
    {
        HbGeneralConfig::operator=( config );
    }

    return *this;
}


bool HbGeneralClientConfig::isValid() const
{
    if( HbGeneralConfig::isValid() )
    {
        // TODO check channel.
        return true;
    }
    return false;
}
