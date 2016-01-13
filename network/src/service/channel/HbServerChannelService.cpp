// Qt
// Hb
#include <HbLogService.h>
// Local
#include <service/channel/HbServerChannelService.h>
#include <service/channel/HbServerChannel.h>
#include <service/channel/HbServerPeopledChannel.h>
#include <contract/channel/HbUserSyncContract.h>

using namespace hb::network;

void HbServerChannelService::reset()
{
    HbChannelService::reset(); // Handles channels unplugging.
    q_assert( mPeopledChannels.size() == 0 );
}

const HbServiceChannelServerConfig & HbServerChannelService::config() const
{
    return mConfig;
}

void HbServerChannelService::setConfig( const HbServiceChannelServerConfig & config )
{
    if( config.isValid() )
    {
        mConfig = config;
    }
}

bool HbServerChannelService::plugChannel( HbNetworkChannel * channel, networkuid network_uid )
{
    bool ok = false;

    if( dynamic_cast< HbServerChannel * >( channel ) )
    {
        ok = HbChannelService::plugChannel( channel, network_uid );

        connect( channel, &HbNetworkChannel::userContractToSend , this, &HbServerChannelService::onUserContractToSend );
        connect( channel, &HbNetworkChannel::usersContractToSend, this, &HbServerChannelService::onUsersContractToSend );
        connect( channel, &HbNetworkChannel::userToKick         , this, &HbServerChannelService::onUserToKick );

        if( ok )
        {
            HbServerPeopledChannel * peopled_channel = dynamic_cast< HbServerPeopledChannel * >( channel );
            if( peopled_channel )
            {
                mPeopledChannels.insert( peopled_channel->uid(), peopled_channel );

                connect( this, &HbServerChannelService::userConnected,    peopled_channel, &HbServerPeopledChannel::onUserConnected );
                connect( this, &HbServerChannelService::userDisconnected, peopled_channel, &HbServerPeopledChannel::onUserDisconnected );
            }
        }
    }

    return ok;
}

bool HbServerChannelService::unplugChannel( HbNetworkChannel * channel )
{
    bool ok = HbChannelService::unplugChannel( channel );

    if( ok )
    {
        disconnect( channel, &HbNetworkChannel::userContractToSend, this, &HbServerChannelService::onUserContractToSend );
        disconnect( channel, &HbNetworkChannel::usersContractToSend, this, &HbServerChannelService::onUsersContractToSend );
        disconnect( channel, &HbNetworkChannel::userToKick, this, &HbServerChannelService::onUserToKick );

        HbServerPeopledChannel * peopled_channel = mPeopledChannels.value( channel->uid(), nullptr );
        if( peopled_channel )
        {
            disconnect( this, &HbServerChannelService::userConnected, peopled_channel, &HbServerPeopledChannel::onUserConnected );
            disconnect( this, &HbServerChannelService::userDisconnected, peopled_channel, &HbServerPeopledChannel::onUserDisconnected );

            mPeopledChannels.remove( peopled_channel->uid() );
        }        
    }

    return ok;
}

HbServerChannel * HbServerChannelService::channel( serviceuid channel_uid )
{
    return dynamic_cast< HbServerChannel * >( HbChannelService::channel( channel_uid ) );
}

void HbServerChannelService::onUserContractReceived( ShConstHbNetworkUserInfo user_info, const HbNetworkContract * contract )
{
    q_assert_ptr( contract );

    serviceuid channel_uid = contract->header().service();

    HbServerChannel * channel = this->channel( channel_uid );
    if( !channel )
    {
        HbError( "Null channel %d.", channel_uid );
        //! \todo Kick user
        delete contract;
        return;
    }

    channel->onUserContractReceived( user_info, contract );
}

void HbServerChannelService::onUserConnected( ShConstHbNetworkUserInfo user_info )
{
    q_assert( !mUsers.contains( user_info->email() ) );

    HbUserSyncContract * one_contract    = new HbUserSyncContract(); // Notify the new connected user.
    HbUserSyncContract * others_contract = new HbUserSyncContract(); // Notify the others.

    HbNetworkUserSync user_sync;
    user_sync.setUserInfo( user_info );
    user_sync.setStatus( HbNetworkProtocol::NETWORK_USER_CONNECTED );

    others_contract->addSync( user_sync );

    auto it = mUsers.begin();
    while( it != mUsers.end() )
    {
        HbNetworkUserSync sync;
        sync.setUserInfo( it.value() );
        sync.setStatus( HbNetworkProtocol::NETWORK_USER_CONNECTED );

        one_contract->addSync( sync );

        ++it;
    }

    emit userContractToSend( user_info, one_contract );
    emit usersContractToSend( mUsers.values(), others_contract );

    mUsers.insert( user_info->email(), user_info );

    emit userConnected( user_info );
}

void HbServerChannelService::onUserDisconnected( ShConstHbNetworkUserInfo user_info )
{
    q_assert( mUsers.contains( user_info->email() ) );

    mUsers.remove( user_info->email() );

    HbUserSyncContract * sync_contract = new HbUserSyncContract(); // Notify the others.

    HbNetworkUserSync user_sync;
    user_sync.setUserInfo( user_info );
    user_sync.setStatus( HbNetworkProtocol::NETWORK_USER_DISCONNECTED );

    sync_contract->addSync( user_sync );

    emit usersContractToSend( mUsers.values(), sync_contract );

    emit userDisconnected( user_info );
}

void HbServerChannelService::onUserContractToSend ( ShConstHbNetworkUserInfo user_info, HbNetworkContract * contract )
{
    q_assert_ptr( contract );
    emit userContractToSend( user_info, contract );
}

void HbServerChannelService::onUsersContractToSend( QList< ShConstHbNetworkUserInfo > users_infos, HbNetworkContract * contract )
{
    q_assert_ptr( contract );
    emit usersContractToSend( users_infos, contract );
}

void HbServerChannelService::onUserToKick  ( ShConstHbNetworkUserInfo user_info, netwint reason, const QString & description )
{
    emit userToKick( user_info, reason, description );
}
