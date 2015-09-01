// Hb
// Local
#include <ServerSumChannel.h>
#include <RequestSumContract.h>
#include <ResponseSumContract.h>
#include <Protocol.h>

using namespace hb::network;
using namespace hb::networkexample;

ServerSumChannel::ServerSumChannel() : HbServerChannel()
{
}

void ServerSumChannel::reset()
{

}

HbNetworkProtocol::NetworkTypes ServerSumChannel::enabledNetworkTypes() const
{
    return HbNetworkProtocol::NETWORK_TCP;
}

void ServerSumChannel::plugContracts( HbNetworkExchanges & exchanges )
{
    exchanges.plug< RequestSumContract >();
}

serviceuid ServerSumChannel::uid() const
{
    return Protocol::CHANNEL_SUM;
}

void ServerSumChannel::onUserContractReceived( const HbNetworkUserData & user_data, const HbNetworkContract * contract )
{

}
