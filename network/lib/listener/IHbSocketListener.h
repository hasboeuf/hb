#ifndef IHBSOCKETLISTENER_H
#define IHBSOCKETLISTENER_H

/*! \file IHbSocketListener.h */

// Hb
#include <HbGlobal.h>
// Local
#include <HbNetwork.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL IHbSocketListener {
public:
    virtual void onSocketConnected(networkuid socket_uid) = 0;
    virtual void onSocketDisconnected(networkuid socket_uid) = 0;

protected:
    virtual ~IHbSocketListener() {
    } //!< \todo defaulted linux-g++ issue
};

} // namespace network
} // namespace hb

using hb::network::IHbSocketListener;

#endif // IHBSOCKETLISTENER_H
