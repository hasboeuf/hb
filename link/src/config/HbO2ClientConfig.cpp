// Local
#include <config/HbO2ClientConfig.h>

using namespace hb::link;

HbO2ClientConfig::HbO2ClientConfig()
{
    mLocalPort = 8080;
}

HbO2ClientConfig::HbO2ClientConfig(const HbO2ClientConfig & config) :
    HbO2Config( config )
{
    if (this != &config)
    {
        mLocalPort     = config.mLocalPort;
        mScope         = config.mScope;
    }
}

HbO2ClientConfig & HbO2ClientConfig::operator =(const HbO2ClientConfig & config)
{
    if (this != &config)
    {
        HbO2Config::operator=( config );

        mLocalPort     = config.mLocalPort;
        mScope         = config.mScope;
    }

    return *this;
}


bool HbO2ClientConfig::isValid() const
{
    if( HbO2Config::isValid() )
    {
        return true;
    }
    return false;
}

bool HbO2ClientConfig::read( QDataStream & stream )
{
    stream >> mScope;
    stream >> mLocalPort;

    return true;
}

bool HbO2ClientConfig::write( QDataStream & stream ) const
{
    stream << mScope;
    stream << mLocalPort;

    return true;
}

void HbO2ClientConfig::setLocalPort( quint16 local_port )
{
    mLocalPort = local_port;
}

quint16 HbO2ClientConfig::localPort() const
{
    return mLocalPort;
}

void HbO2ClientConfig::addScope( const QString & permission )
{
    if( !permission.isEmpty() )
    {
        if( !mScope.isEmpty() )
        {
            mScope += QStringLiteral( "," );
        }
        mScope += permission;
    }
}

const QString & HbO2ClientConfig::scope() const
{
    return mScope;
}
