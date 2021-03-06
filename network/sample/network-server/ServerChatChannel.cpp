// Hb
#include <HbLogService.h>
// Local
#include <ChatMessageBackContract.h>
#include <ChatMessageContract.h>
#include <Protocol.h>
#include <ServerChatChannel.h>

using namespace hb::network;
using namespace hb::networkexample;

ServerChatChannel::ServerChatChannel() : HbServerPeopledChannel() {
}

void ServerChatChannel::reset() {
}

void ServerChatChannel::plugContracts(HbNetworkExchanges& exchanges) {
    exchanges.plug<ChatMessageContract>();
    exchanges.plug<ChatMessageBackContract>();
}

serviceuid ServerChatChannel::uid() const {
    return Protocol::CHANNEL_CHAT;
}

void ServerChatChannel::onUserContractReceived(ShConstHbNetworkUserInfo user_info, const HbNetworkContract* contract) {
    Q_ASSERT(contract);

    qDebug() << "Contract received from" << user_info->email();
    qDebug() << "Contract details:" << contract->toString();

    const ChatMessageContract* message = contract->value<ChatMessageContract>();
    if (message) {
        ChatMessageBackContract* message_back = new ChatMessageBackContract();
        message_back->setAuthor(user_info->firstName());
        message_back->setMessage(message->message());

        onUsersContractToSend(connectedUsers().values(), message_back);
    }

    delete contract;
}
