// Qt
// Hb
#include <HbLogService.h>
// Local
#include <service/channel/HbClientChannelService.h>
#include <service/channel/HbClientChannel.h>
#include <service/channel/HbClientPeopledChannel.h>
#include <contract/channel/HbUserSyncContract.h>

using namespace hb::network;

void HbClientChannelService::reset()
{
    HbChannelService::reset();
}

const HbServiceChannelClientConfig & HbClientChannelService::config() const
{
    return mConfig;
}

void HbClientChannelService::setConfig( const HbServiceChannelClientConfig & config )
{
    if( config.isValid() )
    {
        mConfig = config;
    }
}

bool HbClientChannelService::addChannel( HbNetworkChannel * channel )
{
    bool ok = false;

    if( dynamic_cast< HbClientChannel * >( channel ) )
    {
        ok = HbChannelService::addChannel( channel );

        if( ok )
        {
            HbClientPeopledChannel * peopled_channel = dynamic_cast< HbClientPeopledChannel * >( channel );
            if( peopled_channel )
            {
                mPeopledChannels.insert( peopled_channel->uid(), peopled_channel );

                connect( this, &HbClientChannelService::userConnected,    peopled_channel, &HbClientPeopledChannel::onUserConnected );
                connect( this, &HbClientChannelService::userDisconnected, peopled_channel, &HbClientPeopledChannel::onUserDisconnected );
            }
        }
    }

    return ok;
}

HbClientChannel * HbClientChannelService::channel( serviceuid channel_uid )
{
    return dynamic_cast< HbClientChannel * >( HbChannelService::channel( channel_uid ) );
}

void HbClientChannelService::onUserContractReceived( const HbNetworkContract * contract )
{
    q_assert_ptr( contract );

    serviceuid channel_uid = contract->header().service();

    // Internal contract.
    if( channel_uid == uid() )
    {
        processContract( contract );
    }

    // Channel contract.

    HbClientChannel * channel = this->channel( channel_uid );
    if( !channel )
    {
        HbError( "Null channel %d.", channel_uid );
        delete contract;
        return;
    }

    channel->onUserContractReceived( contract );
}

void HbClientChannelService::onUserConnected( ShConstHbNetworkUserInfo user_info )
{
    emit userConnected( user_info );
}

void HbClientChannelService::onUserDisconnected( ShConstHbNetworkUserInfo user_info )
{
    emit userDisconnected( user_info );
}

void HbClientChannelService::processContract( const HbNetworkContract * contract )
{
    q_assert_ptr( contract );

    const HbUserSyncContract * sync_contract = contract->value< HbUserSyncContract >();
    if( sync_contract )
    {
        foreach( HbNetworkUserSync user_sync, sync_contract->syncs() )
        {
            ShConstHbNetworkUserInfo user_info( new HbNetworkUserInfo( user_sync.userInfo() ) );
            if( user_sync.status() == HbNetworkProtocol::NETWORK_USER_CONNECTED )
            {
                mUsers.insert( user_info->email(), user_info );
                onUserConnected( user_info ); // Simulates user connection.
            }
            else if( user_sync.status() == HbNetworkProtocol::NETWORK_USER_DISCONNECTED )
            {
                mUsers.remove( user_info->email() );
                onUserDisconnected( user_info ); // Simulates user disconnection.
            }
            else
            {
                HbWarning( "User status not recognized." );
            }
        }
    }
    else
    {
        HbError( "Channel contract type not recognized." );
        //! \todo How to kick?
    }

    delete contract;
}
