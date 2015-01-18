#include <contract/HbNetworkHeader.h>

#include <QDataStream>

using namespace hb::network;


HbNetworkHeader::HbNetworkHeader()
{
	_sender = 0;

	_service = HbNetworkContract::UNDEFINED;
	_code = HbNetworkContract::UNDEFINED;
	_routing = HbNetworkContract::RoutingScheme::Unicast;
}

HbNetworkHeader::HbNetworkHeader( quint16 sender ) :
HbNetworkHeader()
{
	_sender = sender;

	_code = (_sender > 0) ? REGISTRATION : HbNetworkContract::UNKNOWN;
	_routing = HbNetworkContract::RoutingScheme::Unicast;
}

HbNetworkHeader::HbNetworkHeader( quint16 sender, const HbNetworkContract * contract ) :
HbNetworkHeader()
{
	_sender = sender;

	if ((_sender > 0) && contract)
		_service = contract->service();

	if (_service == HbNetworkContract::UNDEFINED)
	{
		_code = HbNetworkContract::UNKNOWN;
		_routing = HbNetworkContract::RoutingScheme::Unicast;
	}

	else if (contract->service() != HbNetworkContract::UNDEFINED)
	{
		_code = contract->code();
		_routing = contract->routing();
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

			stream << (qint32)header._routing;
			stream << header._receivers;

			return stream;
		}

		QDataStream & operator >>(QDataStream & stream, HbNetworkHeader & header)
		{
			qint32 enum_stream = 0;

			stream >> header._sender;
			stream >> header._service;
			stream >> header._code;

			stream >> enum_stream;
			stream >> header._receivers;

			header._routing = (HbNetworkContract::RoutingScheme) enum_stream;

			return stream;
		}

	}
}
