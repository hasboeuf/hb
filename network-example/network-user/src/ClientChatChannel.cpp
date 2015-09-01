// Hb
#include <ChatMessageContract.h>
#include <ChatMessageBackContract.h>
// Local
#include <ClientChatChannel.h>
#include <Protocol.h>

using namespace hb::network;
using namespace hb::networkexample;

ClientChatChannel::ClientChatChannel() : HbClientPeopledChannel()
{
}

void ClientChatChannel::reset()
{

}

HbNetworkProtocol::NetworkTypes ClientChatChannel::enabledNetworkTypes() const
{
    return HbNetworkProtocol::NETWORK_TCP;
}

void ClientChatChannel::plugContracts( HbNetworkExchanges & exchanges )
{
    exchanges.plug< ChatMessageBackContract >();
}

serviceuid ClientChatChannel::uid() const
{
    return Protocol::CHANNEL_CHAT;
}

void ClientChatChannel::onUserContractReceived( const HbNetworkUserData & user_data, const HbNetworkContract * contract )
{

}
