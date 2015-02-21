// Hb
#include <HbLogService.h>
// Local
#include <config/HbTcpServerConfig.h>

HbTcpServerConfig::HbTcpServerConfig( const HbTcpServerConfig & config ) :
    HbComConfig( config ), HbTcpConfig( config ), HbServerConfig( config )
{

}

HbTcpServerConfig & HbTcpServerConfig::operator =( const HbTcpServerConfig & config )
{
    if (this != &config)
    {
        HbComConfig::operator=    ( config );
        HbTcpConfig::operator =   ( config );
        HbServerConfig::operator =( config );
    }

    return *this;
}

bool HbTcpServerConfig::isValid( ) const
{
    if ( !HbTcpConfig::isValid() )
    {
        return false;
    }

    if ( !HbServerConfig::isValid() )
    {
        return false;
    }

    return true;
}
