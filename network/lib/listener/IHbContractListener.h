#ifndef IHBCONTRACTLISTENER_H
#define IHBCONTRACTLISTENER_H

/*! \file IHbContractListener.h */

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
class HB_NETWORK_DECL IHbContractListener {
public:
    virtual void onContractReceived(const HbNetworkContract* contract) = 0;

protected:
    virtual ~IHbContractListener() {
    } //!< \todo defaulted linux-g++ issue
};

} // namespace network
} // namespace hb

using hb::network::IHbContractListener;

#endif // IHBCONTRACTLISTENER_H
