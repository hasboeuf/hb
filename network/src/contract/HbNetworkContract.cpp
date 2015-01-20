// Hb
#include <HbLogService.h>
// Local
#include <contract/HbNetworkContract.h>

using namespace hb::network;

HbNetworkContract::HbNetworkContract( HbNetworkProtocol::Service service, HbNetworkProtocol::Code code)
{
	_service = service;
    _code    = code;
    _routing = HbNetworkProtocol::RoutingScheme::UNICAST;
    _reply   = nullptr;
}

HbNetworkContract::HbNetworkContract( const HbNetworkContract & source )
{
    if( &source != this )
    {
        _service = source._service;
        _code    = source._code;
        _routing = source._routing;
        _reply   = source._reply;
    }
}

HbNetworkContract & HbNetworkContract::operator=( const HbNetworkContract & source )
{
    if( &source != this )
    {
        _service = source._service;
        _code = source._code;
        _routing = source._routing;
        _reply = source._reply;
    }
    return ( *this );
}

HbNetworkProtocol::Service HbNetworkContract::service() const
{
	return _service;
}

HbNetworkProtocol::Code HbNetworkContract::code() const
{
	return _code;
}


void HbNetworkContract::setRouting( HbNetworkProtocol::RoutingScheme routing)
{
	if (_routing != routing)
	{
		_routing = routing;

        if (_routing == HbNetworkProtocol::RoutingScheme::BROADCAST )
		{
			if (_receivers.size() > 0)
            {
                HbWarning( "Predefined receivers will be cleared." );
            }
			
			_receivers.clear();
		}

        if (_routing == HbNetworkProtocol::RoutingScheme::UNICAST)
        {
            if (_receivers.size() > 1)
            {
                HbWarning( "Only the first receiver is kept." );

                int receiver = *_receivers.begin();

                _receivers.clear();
                _receivers.insert(receiver);
            }
        }
	}
}

HbNetworkProtocol::RoutingScheme HbNetworkContract::routing() const
{
    if( _routing == HbNetworkProtocol::RoutingScheme::MULTICAST && _receivers.isEmpty() )
    {
        return HbNetworkProtocol::RoutingScheme::BROADCAST;
    }

    return _routing;
}


bool HbNetworkContract::addReceiver( quint16 receiver )
{
    if( _routing == HbNetworkProtocol::RoutingScheme::UNICAST )
    {
        if (!_receivers.isEmpty())
        {
            HbWarning( "A receiver is already defined in unicast mode." );
            return false;
        }

        _receivers.insert(receiver);
        return true;
    }
    else if( _routing == HbNetworkProtocol::RoutingScheme::MULTICAST )
    {
        _receivers.insert(receiver);
        return true;
    }
    else
    {
        HbWarning( "Unable to add a receiver in broadcast mode." );
        return false;
    }
}

bool HbNetworkContract::setReceiver( quint16 receiver )
{
    resetReceivers();
    return addReceiver( receiver );
}

void HbNetworkContract::resetReceivers()
{
	_receivers.clear();
}

const QSet< quint16 > & HbNetworkContract::receivers() const
{
	return _receivers;
}


bool HbNetworkContract::setReply( HbNetworkContract * reply )
{
    if ( reply && ( _reply != reply ) )
	{
        if ( _routing != HbNetworkProtocol::RoutingScheme::UNICAST )
		{
            HbWarning( "Reply only supported in unicast mode." );
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
