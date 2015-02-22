// Local
#include <com/HbAbstractNetwork.h>

using namespace hb::network;

HbAbstractNetwork::HbAbstractNetwork(QObject * parent) :
    QObject(parent)
{
    qRegisterMetaType< networkuid > ( "networkuid"  );
    qRegisterMetaType< serviceuid > ( "serviceuid"  );
    qRegisterMetaType< codeuid >    ( "codeuid"     );
    qRegisterMetaType< contractuid >( "contractuid" );
    qRegisterMetaType< ShConstHbNetworkContract >( "ShConstHbNetworkContract" );
    qRegisterMetaType< ShHbNetworkContract >     ( "ShHbNetworkContract" );
}

const HbNetworkConfig & HbAbstractNetwork::configuration() const
{
    return mConfig;
}
