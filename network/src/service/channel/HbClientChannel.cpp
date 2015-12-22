// Hb
#include <HbLogService.h>
// Local
#include <service/channel/HbClientChannel.h>

using namespace hb::network;

void HbClientChannel::onContractToSend( HbNetworkContract * contract )
{
    if( !contract )
    {
        HbError( "Null contract." );
        return;
    }

    emit contractToSend( contract );
}
