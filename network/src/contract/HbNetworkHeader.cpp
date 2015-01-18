#include <contract/HbNetworkHeader.h>

#include <QDataStream>

using namespace hb::network;


HbNetworkHeader::HbNetworkHeader()
{
    _sender  = 0;
    _service = HbNetworkContract::SERVICE_UNDEFINED;
    _code    = HbNetworkContract::CODE_UNDEFINED;
    _routing = HbNetworkContract::RoutingScheme::UNICAST;
}

HbNetworkHeader::HbNetworkHeader( quint16 sender, const HbNetworkContract * contract ) :
    HbNetworkHeader()
{
	_sender = sender;

    if ( contract )
    {
		_service = contract->service();
    }

    if ( contract->service() != HbNetworkContract::SERVICE_UNDEFINED )
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


HbNetworkContract::Service HbNetworkHeader::service() const
{
	return _service;
}

HbNetworkContract::Code HbNetworkHeader::code() const
{
	return _code;
}


HbNetworkContract::RoutingScheme HbNetworkHeader::routing() const
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
			stream << header._service;
			stream << header._code;
            stream << header._routing;
			stream << header._receivers;

			return stream;
		}

		QDataStream & operator >>(QDataStream & stream, HbNetworkHeader & header)
		{

            quint16 service = HbNetworkContract::SERVICE_UNDEFINED;
            quint16 code = HbNetworkContract::CODE_UNDEFINED;
            quint8 routing = HbNetworkContract::UNICAST;

			stream >> header._sender;
            stream >> service;
            stream >> code;
            stream >> routing;
			stream >> header._receivers;

            header._service = ( HbNetworkContract::Service ) service;
            header._code = ( HbNetworkContract::Code ) code;
            header._routing = ( HbNetworkContract::RoutingScheme ) routing;

			return stream;
		}
	}
}
