#include <contract/HbNetworkHeader.h>

#include <QDataStream>

using namespace hb::network;


HbNetworkHeader::HbNetworkHeader()
{
    mAppName = HbNetworkProtocol::msAppName;
    mProtocolVersion = HbNetworkProtocol::msProtocolVersion;
    mService = HbNetworkProtocol::SERVICE_UNDEFINED;
    mCode    = HbNetworkProtocol::CODE_UNDEFINED;
    mRouting = HbNetworkProtocol::RoutingScheme::UNICAST;
}

HbNetworkHeader::HbNetworkHeader( HbNetworkProtocol::Service service, HbNetworkProtocol::Code code ) :
    HbNetworkHeader()
{
    mService = service;
    mCode = code;
}

HbNetworkHeader::HbNetworkHeader( const HbNetworkHeader & header )
{
    if( &header != this )
    {
        mAppName         = header.mAppName;
        mProtocolVersion = header.mProtocolVersion;
        mService         = header.mService;
        mCode            = header.mCode;
        mRouting         = header.mRouting;
    }
}

HbNetworkHeader & HbNetworkHeader::operator=( const HbNetworkHeader & header )
{
    if( &header != this )
    {
        mAppName         = header.mAppName;
        mProtocolVersion = header.mProtocolVersion;
        mService         = header.mService;
        mCode            = header.mCode;
        mRouting         = header.mRouting;
    }
    return *this;
}

const QString & HbNetworkHeader::appName() const
{
    return mAppName;
}

quint16 HbNetworkHeader::protocolVersion() const
{
    return mProtocolVersion;
}

HbNetworkProtocol::Service HbNetworkHeader::service() const
{
    return mService;
}

HbNetworkProtocol::Code HbNetworkHeader::code() const
{
    return mCode;
}


HbNetworkProtocol::RoutingScheme HbNetworkHeader::routing() const
{
    return mRouting;
}

void HbNetworkHeader::setRouting( HbNetworkProtocol::RoutingScheme routing )
{
    mRouting = routing;
    // TODO logique routing.
}

namespace hb
{
	namespace network
	{

		QDataStream & operator <<(QDataStream & stream, const HbNetworkHeader & header)
		{
            stream << header.mAppName;
            stream << header.mProtocolVersion;
            stream << ( quint16 ) header.mService;
            stream << ( quint16 ) header.mCode;
            stream << ( quint8 ) header.mRouting;

			return stream;
		}

		QDataStream & operator >>(QDataStream & stream, HbNetworkHeader & header)
		{

            quint16 service = HbNetworkProtocol::SERVICE_UNDEFINED;
            quint16 code = HbNetworkProtocol::CODE_UNDEFINED;
            quint8 routing = HbNetworkProtocol::UNICAST;

            stream >> header.mAppName;
            stream >> header.mProtocolVersion;
            stream >> service;
            stream >> code;
            stream >> routing;

            header.mService = ( HbNetworkProtocol::Service ) service;
            header.mCode = ( HbNetworkProtocol::Code ) code;
            header.mRouting = ( HbNetworkProtocol::RoutingScheme ) routing;

			return stream;
		}
	}
}

/*void HbNetworkContract::setRouting( HbNetworkProtocol::RoutingScheme routing)
{
    if (mRouting != routing)
    {
        mRouting = routing;

        if ( mRouting == HbNetworkProtocol::RoutingScheme::BROADCAST )
        {
            if ( mSocketReceivers.size() > 0)
            {
                HbWarning( "Predefined receivers will be cleared." );
            }

            resetReceivers();
        }

        if ( mRouting == HbNetworkProtocol::RoutingScheme::UNICAST )
        {
            if ( mSocketReceivers.size() > 1 )
            {
                HbWarning( "Only the first receiver is kept." );

                int receiver = *mSocketReceivers.begin();

                resetReceivers();
                mSocketReceivers.insert( receiver );
            }
        }
    }
}

HbNetworkProtocol::RoutingScheme HbNetworkContract::routing() const
{
    if( mRouting == HbNetworkProtocol::RoutingScheme::MULTICAST && mSocketReceivers.isEmpty() )
    {
        return HbNetworkProtocol::RoutingScheme::BROADCAST;
    }

    return mRouting;
}*/
