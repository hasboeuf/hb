// Hb
#include <HbLogService.h>
// Local
#include <config/HbTcpConfig.h>
#include <contract/HbComHeader.h>

using namespace hb::com;

HbTcpConfig::HbTcpConfig() :
    HbComConfig()
{
    mAddress = QHostAddress::Null;
    mPort    = 0;
    mOptions = SocketOption::NoOptions;
}

HbTcpConfig::HbTcpConfig( const HbTcpConfig & config ) :
    HbComConfig( config )
{
    if ( this != &config )
    {
        mAddress = config.mAddress;
        mPort    = config.mPort;
        mOptions = config.mOptions;
    }
}


HbTcpConfig & HbTcpConfig::operator =( const HbTcpConfig & config )
{
    if ( this != &config )
    {
        HbComConfig::operator =( config );

        mAddress = config.mAddress;
        mPort    = config.mPort;
        mOptions = config.mOptions;
    }

    return ( *this );
}

bool HbTcpConfig::isValid() const
{
    if( !HbComConfig::isValid() )
    {
        return false;
    }

    if( mAddress.isNull() )
    {
        HbError( "Null address." );
        return false;
    }

    return true;
}

void HbTcpConfig::setAddress( const QString & address )
{
    setAddress( QHostAddress( address ) );
}

void HbTcpConfig::setAddress( const QHostAddress & address )
{
    mAddress = address;
}

void HbTcpConfig::setPort( quint16 port )
{
    mPort = port;
}

const QHostAddress & HbTcpConfig::address() const
{
    return mAddress;
}

quint16 HbTcpConfig::port() const
{
    return mPort;
}

void HbTcpConfig::setOptions( SocketOptions options )
{
    mOptions = options;
}

HbTcpConfig::SocketOptions HbTcpConfig::options() const
{
    return mOptions;
}
