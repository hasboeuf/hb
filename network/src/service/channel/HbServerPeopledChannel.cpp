// Local
#include <service/channel/HbServerPeopledChannel.h>

using namespace hb::network;

void HbServerPeopledChannel::onUserConnected( ShConstHbNetworkUserInfo user_info )
{
    mUsers.insert( user_info->email(), user_info );
    emit userConnected( user_info );
}

void HbServerPeopledChannel::onUserDisconnected( ShConstHbNetworkUserInfo user_info )
{
    mUsers.remove( user_info->email() );
    emit userDisconnected( user_info );
}

const QHash< QString, ShConstHbNetworkUserInfo > & HbServerPeopledChannel::connectedUsers() const
{
    return mUsers;
}
