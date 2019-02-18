#ifndef IHBCLIENTUSERCONTRACTTLISTENER_H
#define IHBCLIENTUSERCONTRACTTLISTENER_H

/*! \file IHbUserContractListener.h */

// Hb
#include <HbGlobal.h>
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkContract.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL IHbClientUserContractListener {
public:
    virtual void onUserContractReceived(const HbNetworkContract* contract) = 0;

protected:
    virtual ~IHbClientUserContractListener() {
    } //!< \todo defaulted linux-g++ issue
};

} // namespace network
} // namespace hb

using hb::network::IHbClientUserContractListener;

#endif // IHBCLIENTUSERCONTRACTTLISTENER_H
