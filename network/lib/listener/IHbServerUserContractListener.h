#ifndef IHBSERVERUSERCONTRACTTLISTENER_H
#define IHBSERVERUSERCONTRACTTLISTENER_H

/*! \file IHbUserContractListener.h */

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
class HB_NETWORK_DECL IHbServerUserContractListener {
public:
    virtual void onUserContractReceived(ShConstHbNetworkUserInfo user_info, const HbNetworkContract* contract) = 0;

protected:
    virtual ~IHbServerUserContractListener() {
    } //!< \todo defaulted linux-g++ issue
};

} // namespace network
} // namespace hb

using hb::network::IHbServerUserContractListener;

#endif // IHBSERVERUSERCONTRACTTLISTENER_H
