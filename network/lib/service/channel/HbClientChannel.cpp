// Hb
#include <HbLogService.h>
// Local
#include <service/channel/HbClientChannel.h>

using namespace hb::network;

void HbClientChannel::onContractToSend(HbNetworkContract* contract) {
    if (!contract) {
        qWarning() << "Null contract";
        return;
    }

    contract->addSocketReceiver(mNetworkUid);

    emit contractToSend(contract);
}
