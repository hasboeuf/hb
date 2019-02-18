#ifndef HBNETWORKUSERINFOMOCK_H
#define HBNETWORKUSERINFOMOCK_H

/*! \file HbNetworkUserInfo.h */

// Qt
// Hb
// Local
#include <user/HbNetworkUserInfo.h>

namespace hb {
namespace network {

/*!
 * TODOC
 */
class HB_NETWORK_DECL HbNetworkUserInfoMock {
public:
    static void mockNetworkUserInfo(HbNetworkUserInfo& user_info);
};

} // namespace network
} // namespace hb

#endif // HBNETWORKUSERINFOMOCK_H
