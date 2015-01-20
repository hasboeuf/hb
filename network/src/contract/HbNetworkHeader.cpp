#include <contract/HbNetworkHeader.h>

#include <QDataStream>

using namespace hb::network;


HbNetworkHeader::HbNetworkHeader()
{
    _sender  = 0;
    _service = HbNetworkProtocol::SERVICE_UNDEFINED;
    _code    = HbNetworkProtocol::CODE_UNDEFINED;
    _routing = HbNetworkProtocol::RoutingScheme::UNICAST;
}

HbNetworkHeader::HbNetworkHeader( quint16 sender, const HbNetworkContract * contract ) :
    HbNetworkHeader()
{
	_sender = sender;

    if ( contract )
    {
		_service = contract->service();
    }

    if ( contract->service() != HbNetworkProtocol::SERVICE_UNDEFINED )
	{
        _code      = contract->code();
        _routing   = contract->routing();
		_receivers = contract->receivers();
	}
}


quint16 HbNetworkHeader::sender( ) const
{
	return _sender;
}


HbNetworkProtocol::Service HbNetworkHeader::service() const
{
	return _service;
}

HbNetworkProtocol::Code HbNetworkHeader::code() const
{
	return _code;
}


HbNetworkProtocol::RoutingScheme HbNetworkHeader::routing() const
{
	return _routing;
}

const QSet< quint16 > & HbNetworkHeader::receivers( ) const
{
	return _receivers;
}


namespace hb
{
	namespace network
	{

		QDataStream & operator <<(QDataStream & stream, const HbNetworkHeader & header)
		{
			stream << header._sender;
            stream << ( quint16 ) header._service;
            stream << ( quint16 ) header._code;
            stream << ( quint8 ) header._routing;
			stream << header._receivers;

			return stream;
		}

		QDataStream & operator >>(QDataStream & stream, HbNetworkHeader & header)
		{

            quint16 service = HbNetworkProtocol::SERVICE_UNDEFINED;
            quint16 code = HbNetworkProtocol::CODE_UNDEFINED;
            quint8 routing = HbNetworkProtocol::UNICAST;

			stream >> header._sender;
            stream >> service;
            stream >> code;
            stream >> routing;
			stream >> header._receivers;

            header._service = ( HbNetworkProtocol::Service ) service;
            header._code = ( HbNetworkProtocol::Code ) code;
            header._routing = ( HbNetworkProtocol::RoutingScheme ) routing;

			return stream;
		}
	}
}
