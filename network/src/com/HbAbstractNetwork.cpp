// Local
#include <com/HbAbstractNetwork.h>

using namespace hb::network;

HbAbstractNetwork::HbAbstractNetwork(QObject * parent) :
    QObject(parent)
{
    qRegisterMetaType< networkuid >( "netwuid" );
    qRegisterMetaType< serviceuid >( "servuid" );
    qRegisterMetaType< codeuid >( "codeuid" );
    qRegisterMetaType< contractuid >( "ctctuid" );
    qRegisterMetaType< ShConstHbNetworkContract >( "ShConstHbNetworkContract" );
    qRegisterMetaType< ShHbNetworkContract >     ( "ShHbNetworkContract" );
}

const HbNetworkConfig & HbAbstractNetwork::configuration() const
{
    return mConfig;
}
