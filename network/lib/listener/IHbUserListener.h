#ifndef IHBUSERTLISTENER_H
#define IHBUSERTLISTENER_H

/*! \file IHbUserListener.h */

// Hb
#include <HbGlobal.h>
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkContract.h>
#include <user/HbNetworkUserInfo.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL IHbUserListener {
public:
    virtual void onUserConnected(ShConstHbNetworkUserInfo user_info) = 0;
    virtual void onUserDisconnected(ShConstHbNetworkUserInfo user_info) = 0;

protected:
    virtual ~IHbUserListener() {
    } //!< \todo defaulted linux-g++ issue
};

} // namespace network
} // namespace hb

using hb::network::IHbUserListener;

#endif // IHBUSERTLISTENER_H
