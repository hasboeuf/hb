// Hb
#include <RequestSumContract.h>
#include <ResponseSumContract.h>
// Local
#include <ClientSumChannel.h>
#include <Protocol.h>

using namespace hb::network;
using namespace hb::networkexample;

ClientSumChannel::ClientSumChannel() : HbClientChannel()
{
}

void ClientSumChannel::reset()
{

}

HbNetworkProtocol::NetworkTypes ClientSumChannel::enabledNetworkTypes() const
{
    return HbNetworkProtocol::NETWORK_TCP;
}

void ClientSumChannel::plugContracts( HbNetworkExchanges & exchanges )
{
    exchanges.plug< ResponseSumContract >();
}

serviceuid ClientSumChannel::uid() const
{
    return Protocol::CHANNEL_SUM;
}

void ClientSumChannel::onUserContractReceived( const HbNetworkUserData & user_data, const HbNetworkContract * contract )
{
    // TODO
}
