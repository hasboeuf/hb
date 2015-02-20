// Hb
#include <HbLogService.h>
// Local
#include <config/HbTcpClientConfig.h>

HbTcpClientConfig::HbTcpClientConfig( const HbTcpClientConfig & config ) :
    HbComConfig( config ), HbTcpConfig( config ), HbClientConfig( config )
{

}

HbTcpClientConfig & HbTcpClientConfig::operator =( const HbTcpClientConfig & config )
{
    if (this != &config)
    {
        HbComConfig::operator=( config );
        HbTcpConfig::operator =(config);
        HbClientConfig::operator =( config );
    }

    return *this;
}

bool HbTcpClientConfig::isValid( ) const
{
    if ( !HbTcpConfig::isValid() )
    {
        return false;
    }

    if ( !HbClientConfig::isValid() )
    {
        return false;
    }

    return true;
}
