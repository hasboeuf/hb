// Local
#include <HbAbstractCom.h>

using namespace hb::com;

HbAbstractCom::HbAbstractCom(QObject * parent) :
    QObject(parent)
{
    qRegisterMetaType< sockuid >( "sockuid" );
    qRegisterMetaType< netwuid >( "netwuid" );
    qRegisterMetaType< servuid >( "servuid" );
    qRegisterMetaType< codeuid >( "codeuid" );
    qRegisterMetaType< ctctuid >( "ctctuid" );
    qRegisterMetaType< ShConstHbComContract >( "ShConstHbComContract" );
    qRegisterMetaType< ShHbComContract >( "ShHbComContract" );
}

//void HbAbstractCom::addListener(IHbComListener * listener)
//{
//    if (listener)
//    {
//        if (!_listeners.contains(listener))
//            _listeners.append(listener);
//    }
//}

//void HbAbstractCom::removeListener(IHbComListener * listener)
//{
//    _listeners.removeAll(listener);
//}

//const QList< IHbComListener * > & HbAbstractCom::listeners() const
//{
//    return _listeners;
//}

const HbComConfig & HbAbstractCom::configuration() const
{
    return mConfig;
}
