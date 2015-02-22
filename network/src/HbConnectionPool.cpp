// Qt
// Hb
#include <HbGlobal.h>
#include <HbLogService.h>
// Local
#include <HbConnectionPool.h>
#include <service/HbNetworkService.h>


using namespace hb::network;

HbConnectionPool::HbConnectionPool( const HbGeneralConfig & config )
{

}

void HbConnectionPool::setExchanges( HbNetworkExchanges & exchanges )
{
    foreach( HbNetworkService * service, mServices )
    {
        service->plugContracts( exchanges );
    }
}

bool HbConnectionPool::checkContractReceived( const HbNetworkContract * contract )
{
    q_assert_ptr( contract );

    bool ok = true;

    if( ( contract->header().appName()         != HbNetworkProtocol::msAppName ) ||
        ( contract->header().protocolVersion() != HbNetworkProtocol::msProtocolVersion ) )
    {
        ok = false;
    }

    return ok;
}

HbNetworkService * HbConnectionPool::getService( servuid service_uid )
{
    return mServices.value( service_uid, nullptr );
}
