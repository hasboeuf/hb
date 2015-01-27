// Local
#include <config/HbGeneralConfig.h>

using namespace hb::network;


HbGeneralConfig::HbGeneralConfig()
{
    mAppName = "";
    mProtocolVersion = 0;
    mpAuthenticationStrategy = nullptr;
}

HbGeneralConfig::HbGeneralConfig(const HbGeneralConfig & config)
{
	if (this != &config)
	{

	}
}


HbGeneralConfig & HbGeneralConfig::operator =(const HbGeneralConfig & config)
{
	if (this != &config)
	{

	}

	return *this;
}


bool HbGeneralConfig::isValid() const
{
    return ( !mAppName.isEmpty() );
}

const QString & HbGeneralConfig::appName() const
{
    return mAppName;
}

quint16 HbGeneralConfig::protocolVersion() const
{
    return mProtocolVersion;
}

void HbGeneralConfig::setAppName( const QString & app_name )
{
    if( !app_name.isEmpty() )
    {
        mAppName = app_name;
    }
}

void HbGeneralConfig::setProtocolVersion( quint16 protocol_version )
{
    mProtocolVersion = protocol_version;
}
