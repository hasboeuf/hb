// Hb
// Local
#include <ServerChatChannel.h>
#include <ChatMessageBackContract.h>
#include <ChatMessageContract.h>
#include <Protocol.h>

using namespace hb::network;
using namespace hb::networkexample;

ServerChatChannel::ServerChatChannel() : HbServerPeopledChannel()
{
}

void ServerChatChannel::reset()
{

}

HbNetworkProtocol::NetworkTypes ServerChatChannel::enabledNetworkTypes() const
{
    return HbNetworkProtocol::NETWORK_TCP;
}

void ServerChatChannel::plugContracts( HbNetworkExchanges & exchanges )
{
    exchanges.plug< ChatMessageContract >();
}

serviceuid ServerChatChannel::uid() const
{
    return Protocol::CHANNEL_CHAT;
}

void ServerChatChannel::onUserContractReceived( const HbNetworkUserData & user_data, const HbNetworkContract * contract )
{

}
