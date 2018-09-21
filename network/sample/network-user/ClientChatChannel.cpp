// Hb
#include <HbLogService.h>
// Local
#include <ChatMessageBackContract.h>
#include <ChatMessageContract.h>
#include <ClientChatChannel.h>
#include <Protocol.h>

using namespace hb::network;
using namespace hb::networkexample;

ClientChatChannel::ClientChatChannel() : HbClientPeopledChannel() {
}

void ClientChatChannel::reset() {
}

void ClientChatChannel::plugContracts(HbNetworkExchanges& exchanges) {
    exchanges.plug<ChatMessageContract>();
    exchanges.plug<ChatMessageBackContract>();
}

serviceuid ClientChatChannel::uid() const {
    return Protocol::CHANNEL_CHAT;
}

void ClientChatChannel::sendMessage(const QString message) {
    if (message.isEmpty()) {
        qWarning() << "Not enable to send empty chat message";
        return;
    }

    ChatMessageContract* message_contract = new ChatMessageContract();
    message_contract->setMessage(message);

    onContractToSend(message_contract);
}

void ClientChatChannel::onUserContractReceived(const HbNetworkContract* contract) {
    q_assert_ptr(contract);

    qDebug() << "Contract received from" << contract->sender();
    qDebug() << "Contract details:" << contract->toString();

    const ChatMessageBackContract* message_contract = contract->value<ChatMessageBackContract>();
    if (message_contract) {
        emit chatMessageReceived(message_contract->author(), message_contract->message());
    }

    delete contract;
}
