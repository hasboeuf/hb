// Local
#include <HbNetworkContract.h>

HbNetworkContract::HbNetworkContract(Service service, Code code)
{
	_service = service;
	_code = (_service != UNDEFINED) ? code : UNKNOWN;
	_routing = RoutingScheme::Unicast;

	_reply = nullptr;
}


void HbNetworkContract::reset()
{
}


HbNetworkContract::Service HbNetworkContract::service() const
{
	return _service;
}

HbNetworkContract::Code HbNetworkContract::code() const
{
	return _code;
}


void HbNetworkContract::setRouting(RoutingScheme routing)
{
	if (_routing != routing)
	if (_service != UNDEFINED)
	{
		_routing = routing;

		if (_routing == RoutingScheme::Broadcast)
		{
			if (_receivers.size() > 0)
				qWarning("HbNetworkContract::setRouting() -> predefined receivers will be cleared");
			
			_receivers.clear();
		}

		if (_routing == RoutingScheme::Unicast)
		if (_receivers.size() > 1)
		{
			int receiver = *_receivers.begin();
		
			_receivers.clear();
			_receivers.insert(receiver);
		}
	}
}

HbNetworkContract::RoutingScheme HbNetworkContract::routing() const
{
	return ((_routing == RoutingScheme::Multicast) /*&& _receivers.isEmpty()*/) ?
		RoutingScheme::Broadcast : _routing;
}


bool HbNetworkContract::addReceiver(int receiver)
{
	if (_service != UNDEFINED)
	{
		if (!receiver)
		{
			qWarning("HbNetworkContract::addReceiver() -> set a null receiver is not allowed");
			return false;
		}

		switch (_routing)
		{
		case RoutingScheme::Unicast:

			if (!_receivers.isEmpty())
			{
				qWarning("HbNetworkContract::addReceiver() -> a receiver is already defined in unicast mode");
				return false;
			}

			_receivers.insert(receiver);
			return true;

		case RoutingScheme::Multicast:

			_receivers.insert(receiver);
			return true;

		default:

			qWarning("HbNetworkContract::addReceiver() -> unable to add a receiver in broadcast mode");
			return false;
		}
	}

	return false;
}

bool HbNetworkContract::setReceiver(int receiver)
{
	_receivers.clear();
	return addReceiver(receiver);
}

void HbNetworkContract::resetReceivers()
{
	_receivers.clear();
}

const QSet< int > & HbNetworkContract::receivers() const
{
	return _receivers;
}


bool HbNetworkContract::setReply(HbNetworkContract * reply)
{
	if (_reply != reply)
	{
		if (reply && (_routing != RoutingScheme::Unicast))
		{
			qWarning("HbNetworkContract::setReply() -> reply only supported in unicast mode");
			return false;
		}

		_reply = reply;
	}

	return true;
}

HbNetworkContract * HbNetworkContract::reply() const
{
	return _reply;
}
