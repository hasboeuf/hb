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


HbNetworkContract * HbAbstractNetwork::Exchanges::add(HbNetworkContract * contract)
{
	Contracts & contracts = _contracts[q_assert_ptr(contract)->service()];
	HbNetworkContract * insertable = contracts.value(contract->code());

	if (insertable)
	{
		delete contract;
		return insertable;
	}

	contracts.insert(contract->code(), contract);
	return contract;
}

void HbAbstractNetwork::Exchanges::remove(HbNetworkContract * contract)
{
	HbNetworkContract * removable = q_assert_ptr(contract);

	removable = _contracts.value(removable->service()).value(removable->code());
	if (removable != contract) delete contract;

	if (removable)
	{
		Contracts & contracts = _contracts[removable->service()];
		contracts.remove(removable->code());

		if (contracts.isEmpty())
			_contracts.remove(removable->service());

		delete removable;
	}
}

bool HbAbstractNetwork::Exchanges::registered(
	HbNetworkContract::Service service, HbNetworkContract::Code code) const
{
	return _contracts.value(service).contains(code);
}

HbNetworkContract * HbAbstractNetwork::Exchanges::contract(
	HbNetworkContract::Service service, HbNetworkContract::Code code) const
{
	return _contracts.value(service).value(code);
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
