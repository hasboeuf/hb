// Hb
#include <HbLogService.h>
// Local
#include <Protocol.h>
#include <RequestSumContract.h>
#include <ResponseSumContract.h>
#include <ServerSumChannel.h>

using namespace hb::network;
using namespace hb::networkexample;

ServerSumChannel::ServerSumChannel() : HbServerChannel() {
}

void ServerSumChannel::reset() {
}

void ServerSumChannel::plugContracts(HbNetworkExchanges& exchanges) {
    exchanges.plug<RequestSumContract>();
    exchanges.plug<ResponseSumContract>();
}

serviceuid ServerSumChannel::uid() const {
    return Protocol::CHANNEL_SUM;
}

void ServerSumChannel::onUserContractReceived(ShConstHbNetworkUserInfo user_info, const HbNetworkContract* contract) {
    Q_ASSERT(contract);

    qDebug() << "Contract received from" << user_info->email();
    qDebug() << "Contract details:" << contract->toString();

    const RequestSumContract* sum_contract = contract->value<RequestSumContract>();
    if (sum_contract) {
        ResponseSumContract* result_contract = sum_contract->takeReply();
        if (result_contract) {
            result_contract->setResult(sum_contract->intA() + sum_contract->intB());
            onContractToSend(result_contract);
        }
    }

    delete contract;
}
