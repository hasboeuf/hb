// Local
#include <com/HbAbstractNetwork.h>

using namespace hb::network;

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

HbNetworkConfig & HbAbstractNetwork::configuration()
{
	return _config;
}
