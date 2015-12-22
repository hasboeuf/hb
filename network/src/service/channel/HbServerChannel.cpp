// Hb
#include <HbLogService.h>
// Local
#include <service/channel/HbServerChannel.h>

using namespace hb::network;

void HbServerChannel::onContractToSend( HbNetworkContract * contract )
{
    // Function used to send a reply contract from a channel.

    if( !contract )
    {
        HbError( "Null contract." );
        return;
    }

    if( contract->routing() != HbNetworkProtocol::ROUTING_UNICAST )
    {
        HbError( "Only unicast contract are supported." );
        delete contract;
        return;
    }

    if( contract->receivers().size() != 1 )
    {
        HbError( "There must be only one receiver." );
    }

    emit contractToSend( contract );
}

void HbServerChannel::onUserContractToSend ( ShConstHbNetworkUserInfo user_info, HbNetworkContract * contract )
{
    if( !contract )
    {
        HbError( "Null contract." );
        return;
    }

    contract->setNetworkReceiver( mNetworkUid );

    emit userContractToSend( user_info, contract );
}

void HbServerChannel::onUsersContractToSend( QList< ShConstHbNetworkUserInfo > users_infos, HbNetworkContract * contract )
{
    if( !contract )
    {
        HbError( "Null contract." );
        return;
    }

    contract->setNetworkReceiver( mNetworkUid );

    emit usersContractToSend( users_infos, contract );
}

void HbServerChannel::onUserToKick  ( ShConstHbNetworkUserInfo user_info, netwint reason, const QString & description )
{
    emit userToKick( user_info, reason, description );
}
