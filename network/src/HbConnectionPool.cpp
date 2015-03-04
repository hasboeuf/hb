// Qt
// Hb
#include <HbGlobal.h>
#include <HbLogService.h>
// Local
#include <HbConnectionPool.h>
#include <service/HbNetworkService.h>
#include <contract/general/HbKickContract.h>

using namespace hb::network;

HbConnectionPool::HbConnectionPool( const HbGeneralConfig & config )
{
    qRegisterMetaType< HbNetworkProtocol::ServerStatus >( "HbNetworkProtocol::ServerStatus" );
    qRegisterMetaType< HbNetworkProtocol::ClientStatus >( "HbNetworkProtocol::ClientStatus" );
    qRegisterMetaType< HbNetworkProtocol::UserStatus >  ( "HbNetworkProtocol::UserStatus" );
}

void HbConnectionPool::setExchanges( HbNetworkExchanges & exchanges )
{
    exchanges.plug< HbKickContract >();

    foreach( HbNetworkService * service, mServices )
    {
        service->plugContracts( exchanges );
    }
}

HbNetworkService * HbConnectionPool::getService( serviceuid service_uid )
{
    return mServices.value( service_uid, nullptr );
}
