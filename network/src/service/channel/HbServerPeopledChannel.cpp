// Local
#include <service/channel/HbServerPeopledChannel.h>

using namespace hb::network;

void HbServerPeopledChannel::onUserConnected( const HbNetworkUserData & user_data )
{
    mUsers.insert( user_data.info()->email(), user_data );
    emit userConnected( HbNetworkUserInfo( *user_data.info() ) );
}

void HbServerPeopledChannel::onUserDisconnected( const HbNetworkUserData & user_data )
{
    mUsers.remove( user_data.info()->email() );
    emit userDisconnected( HbNetworkUserInfo( *user_data.info() ) );
}
