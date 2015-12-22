// Hb
#include <HbLogService.h>
// Local
#include <ClientSumChannel.h>
#include <RequestSumContract.h>
#include <ResponseSumContract.h>
#include <Protocol.h>

using namespace hb::network;
using namespace hb::networkexample;

ClientSumChannel::ClientSumChannel() : HbClientChannel()
{
}

void ClientSumChannel::reset()
{

}

void ClientSumChannel::plugContracts( HbNetworkExchanges & exchanges )
{
    exchanges.plug< ResponseSumContract >();
}

serviceuid ClientSumChannel::uid() const
{
    return Protocol::CHANNEL_SUM;
}

void ClientSumChannel::onUserContractReceived( const HbNetworkContract * contract )
{
    q_assert_ptr( contract );

    HbInfo( "Contract received from %d.", HbLatin1( contract->sender() ) );
    HbInfo( "Contract details: %s", HbLatin1( contract->toString() ) );

    const ResponseSumContract * result_contract = contract->value< ResponseSumContract >();
    if( result_contract )
    {
        emit computationReceived( result_contract->result() );
    }

    delete contract;
}

void ClientSumChannel::requestSum( quint32 a, quint32 b )
{
    RequestSumContract * contract = new RequestSumContract();
    contract->setIntA( a );
    contract->setIntB( b );

    onContractToSend( contract );
}
