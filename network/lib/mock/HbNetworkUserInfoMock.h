/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

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
class HB_NETWORK_DECL HbNetworkUserInfoMock final {
public:
    static void mockNetworkUserInfo(HbNetworkUserInfo& user_info);
};

} // namespace network
} // namespace hb

#endif // HBNETWORKUSERINFOMOCK_H
