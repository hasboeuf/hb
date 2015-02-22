// Local
#include <com/HbAbstractNetwork.h>

using namespace hb::network;

HbAbstractNetwork::HbAbstractNetwork(QObject * parent) :
    QObject(parent)
{
    qRegisterMetaType< sockuid >( "sockuid" );
    qRegisterMetaType< netwuid >( "netwuid" );
    qRegisterMetaType< servuid >( "servuid" );
    qRegisterMetaType< codeuid >( "codeuid" );
    qRegisterMetaType< ctctuid >( "ctctuid" );
    qRegisterMetaType< ShConstHbNetworkContract >( "ShConstHbNetworkContract" );
    qRegisterMetaType< ShHbNetworkContract >     ( "ShHbNetworkContract" );
}

const HbNetworkConfig & HbAbstractNetwork::configuration() const
{
    return mConfig;
}
