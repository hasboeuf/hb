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
    qRegisterMetaType< ShHbComContract >     ( "ShHbComContract" );
}

const HbComConfig & HbAbstractCom::configuration() const
{
    return mConfig;
}
