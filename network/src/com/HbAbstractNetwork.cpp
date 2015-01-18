// Local
#include <com/HbAbstractNetwork.h>

using namespace hb::network;


HbAbstractNetwork::Exchanges::~Exchanges()
{
	foreach(const Contracts & contracts, _contracts)
	{
		foreach(HbNetworkContract * contract, contracts)
			delete contract;
	}
}


bool HbAbstractNetwork::Exchanges::add(HbNetworkContract * contract)
{
    if( !contract )
    {
        return false;
    }


    Contracts & contracts = _contracts[ contract->service() ];
    HbNetworkContract * existing_contract = contracts.value( contract->code(), nullptr );

    if ( existing_contract )
	{
		delete contract;
	}
    else
    {
        contracts.insert( contract->code(), contract );
    }

    return true;
}

bool HbAbstractNetwork::Exchanges::remove( HbNetworkContract * contract )
{
    if( !contract )
    {
        return false;
    }

    HbNetworkContract * existing_contract = _contracts.value( contract->service() ).value( contract->code(), nullptr );

    if ( contract != existing_contract)
    {
        delete contract;
    }

    if ( existing_contract )
	{
        Contracts & contracts = _contracts[ existing_contract->service() ];
        contracts.remove( existing_contract->code() );

        if (contracts.isEmpty() )
        {
            _contracts.remove( existing_contract->service() );
        }

        delete existing_contract;
        return true;
	}
    else
    {
        return false;
    }
}

bool HbAbstractNetwork::Exchanges::registered( HbNetworkContract::Service service, HbNetworkContract::Code code ) const
{
    return _contracts.value( service ).contains( code );
}

HbNetworkContract * HbAbstractNetwork::Exchanges::contract( HbNetworkContract::Service service, HbNetworkContract::Code code) const
{
    return _contracts.value( service ).value( code );
}

HbAbstractNetwork::HbAbstractNetwork(QObject * parent) :
	QObject(parent)
{

}

//void HbAbstractNetwork::addListener(IHbNetworkListener * listener)
//{
//	if (listener)
//	{
//		if (!_listeners.contains(listener))
//			_listeners.append(listener);
//	}
//}

//void HbAbstractNetwork::removeListener(IHbNetworkListener * listener)
//{
//	_listeners.removeAll(listener);
//}

//const QList< IHbNetworkListener * > & HbAbstractNetwork::listeners() const
//{
//	return _listeners;
//}

const HbNetworkConfig & HbAbstractNetwork::configuration( ) const
{
	return _config;
}

HbAbstractNetwork::Exchanges & HbAbstractNetwork::exchanges()
{
	return _exchanges;
}

const HbAbstractNetwork::Exchanges & HbAbstractNetwork::exchanges() const
{
	return _exchanges;
}
