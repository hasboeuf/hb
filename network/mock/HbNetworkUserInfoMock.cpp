// Qt
// Hb
#include <core/HbStringHelper.h>
// Local
#include <mock/HbNetworkUserInfoMock.h>

using namespace hb::network;
using namespace hb::tools;

void HbNetworkUserInfoMock::mockNetworkUserInfo( HbNetworkUserInfo & user_info )
{
    QString random_numbers = HbStringHelper::randomString( 3, "0123456789" );
    QString random_letters = HbStringHelper::randomString( 3 );

    user_info.setId       ( user_info.id() + random_numbers );
    user_info.setEmail    ( random_letters + user_info.email() );
    user_info.setFirstName( random_letters + user_info.firstName() );
    user_info.setNickname ( user_info.firstName() + " " +
                            user_info.lastName() );
}
