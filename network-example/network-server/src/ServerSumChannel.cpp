// Hb
#include <HbLogService.h>
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

void ServerSumChannel::plugContracts( HbNetworkExchanges & exchanges )
{
    exchanges.plug< RequestSumContract >();
    exchanges.plug< ResponseSumContract >();
}

serviceuid ServerSumChannel::uid() const
{
    return Protocol::CHANNEL_SUM;
}

void ServerSumChannel::onUserContractReceived( ShConstHbNetworkUserInfo user_info, const HbNetworkContract * contract )
{
    q_assert_ptr( contract );

    HbInfo( "Contract received from %d.", HbLatin1( user_info->email() ) );
    HbInfo( "Contract details: %s", HbLatin1( contract->toString() ) );

    const RequestSumContract * sum_contract = contract->value< RequestSumContract >();
    if( sum_contract )
    {
        ResponseSumContract * result_contract = sum_contract->takeReply();
        if( result_contract )
        {
            result_contract->setResult( sum_contract->intA() + sum_contract->intB() );
            onContractToSend( result_contract );
        }
    }

    delete contract;
}
