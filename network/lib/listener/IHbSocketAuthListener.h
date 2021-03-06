#ifndef IHBSOCKETAUTHLISTENER_H
#define IHBSOCKETAUTHLISTENER_H

/*! \file IHbSocketAuthListener.h */

// Hb
#include <HbGlobal.h>
// Local
#include <HbNetwork.h>
#include <user/HbNetworkUserInfo.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL IHbSocketAuthListener {
public:
    virtual void onSocketAuthenticated(networkuid socket_uid) = 0;
    virtual void onSocketUnauthenticated(networkuid socket_uid) = 0;

protected:
    virtual ~IHbSocketAuthListener() {
    } //!< \todo defaulted linux-g++ issue
};

} // namespace network
} // namespace hb

using hb::network::IHbSocketAuthListener;

#endif // IHBSOCKETAUTHLISTENER_H
