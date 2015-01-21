#include <contract/HbNetworkHeader.h>

#include <QDataStream>

using namespace hb::network;


HbNetworkHeader::HbNetworkHeader()
{
    mSender  = 0;
    mService = HbNetworkProtocol::SERVICE_UNDEFINED;
    mCode    = HbNetworkProtocol::CODE_UNDEFINED;
    mRouting = HbNetworkProtocol::RoutingScheme::UNICAST;
}

HbNetworkHeader::HbNetworkHeader( quint16 sender, const HbNetworkContract * contract ) :
    HbNetworkHeader()
{
    mSender = sender;

    if ( contract )
    {
        mService = contract->service();
    }

    if ( contract->service() != HbNetworkProtocol::SERVICE_UNDEFINED )
	{
        mCode      = contract->code();
        mRouting   = contract->routing();
        mReceivers = contract->receivers();
	}
}


quint16 HbNetworkHeader::sender( ) const
{
    return mSender;
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

const QSet< quint16 > & HbNetworkHeader::receivers( ) const
{
    return mReceivers;
}


namespace hb
{
	namespace network
	{

		QDataStream & operator <<(QDataStream & stream, const HbNetworkHeader & header)
		{
            stream << header.mSender;
            stream << ( quint16 ) header.mService;
            stream << ( quint16 ) header.mCode;
            stream << ( quint8 ) header.mRouting;
            stream << header.mReceivers;

			return stream;
		}

		QDataStream & operator >>(QDataStream & stream, HbNetworkHeader & header)
		{

            quint16 service = HbNetworkProtocol::SERVICE_UNDEFINED;
            quint16 code = HbNetworkProtocol::CODE_UNDEFINED;
            quint8 routing = HbNetworkProtocol::UNICAST;

            stream >> header.mSender;
            stream >> service;
            stream >> code;
            stream >> routing;
            stream >> header.mReceivers;

            header.mService = ( HbNetworkProtocol::Service ) service;
            header.mCode = ( HbNetworkProtocol::Code ) code;
            header.mRouting = ( HbNetworkProtocol::RoutingScheme ) routing;

			return stream;
		}
	}
}
