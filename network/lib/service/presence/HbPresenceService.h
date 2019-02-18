#ifndef HBPRESENCESERVICE_H
#define HBPRESENCESERVICE_H

/*! \file HbPresenceService.h */

// Qt
// Hb
// Local
#include <listener/IHbSocketAuthListener.h>
#include <service/HbNetworkService.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbPresenceService : public HbNetworkService, public IHbSocketAuthListener {
public:
    HbPresenceService();
    virtual ~HbPresenceService() {
    } //!< \todo defaulted linux-g++ issue

    virtual void plugContracts(HbNetworkExchanges& exchanges) override;

    virtual serviceuid uid() const override;
};
} // namespace network
} // namespace hb

#endif // HBPRESENCESERVICE_H
