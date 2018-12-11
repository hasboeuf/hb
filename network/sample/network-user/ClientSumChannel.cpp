// Hb
#include <HbLogService.h>
// Local
#include <ClientSumChannel.h>
#include <Protocol.h>
#include <RequestSumContract.h>
#include <ResponseSumContract.h>

using namespace hb::network;
using namespace hb::networkexample;

ClientSumChannel::ClientSumChannel() : HbClientChannel() {
}

void ClientSumChannel::reset() {
}

void ClientSumChannel::plugContracts(HbNetworkExchanges& exchanges) {
    exchanges.plug<RequestSumContract>();
    exchanges.plug<ResponseSumContract>();
}

serviceuid ClientSumChannel::uid() const {
    return Protocol::CHANNEL_SUM;
}

void ClientSumChannel::onUserContractReceived(const HbNetworkContract* contract) {
    Q_ASSERT(contract);

    qDebug() << "Contract received from" << contract->sender();
    qDebug() << "Contract details:" << contract->toString();

    const ResponseSumContract* result_contract = contract->value<ResponseSumContract>();
    if (result_contract) {
        emit computationReceived(result_contract->result());
    }

    delete contract;
}

void ClientSumChannel::requestSum(quint32 a, quint32 b) {
    RequestSumContract* contract = new RequestSumContract();
    contract->setIntA(a);
    contract->setIntB(b);

    onContractToSend(contract);
}
