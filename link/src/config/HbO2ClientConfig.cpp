// Hb
#include <HbLogService.h>
// Local
#include <config/HbO2ClientConfig.h>

using namespace hb::link;

HbO2ClientConfig::HbO2ClientConfig()
{
    mLocalPort = 8080;
    mScopesSeparator = ",";
}

HbO2ClientConfig::HbO2ClientConfig(const HbO2ClientConfig & config) :
    HbO2Config( config )
{
    if (this != &config)
    {
        mLocalPort     = config.mLocalPort;
        mScopes         = config.mScopes;
    }
}

HbO2ClientConfig & HbO2ClientConfig::operator =(const HbO2ClientConfig & config)
{
    if (this != &config)
    {
        HbO2Config::operator=( config );

        mLocalPort     = config.mLocalPort;
        mScopes         = config.mScopes;
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
    stream >> mScopes;
    stream >> mLocalPort;

    return true;
}

bool HbO2ClientConfig::write( QDataStream & stream ) const
{
    stream << mScopes;
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
        mScopes << permission;
    }
}

void HbO2ClientConfig::setScopes( const QStringList & permissions )
{
    if( mScopes.isEmpty() )
    {
        mScopes = permissions;
    }
    else
    {
        HbWarning( "Scope is not empty." );
    }
}

const QStringList & HbO2ClientConfig::scopes() const
{
    return mScopes;
}

QString HbO2ClientConfig::scopesStr() const
{
    return mScopes.join( mScopesSeparator );
}

void HbO2ClientConfig::setScopeSeparator( const QString & separator )
{
    mScopesSeparator = separator;
}
