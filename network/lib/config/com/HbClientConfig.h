#ifndef HBCLIENTCONFIG_H
#define HBCLIENTCONFIG_H

/*! \file HbClientConfig.h */

// Qt
#include <QtCore/QtGlobal>
// Local
#include <HbNetwork.h>
#include <config/com/HbNetworkConfig.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbClientConfig : public virtual HbNetworkConfig {
public:
    HbClientConfig();
    virtual ~HbClientConfig() = default;
    HbClientConfig(const HbClientConfig& config);
    HbClientConfig& operator=(const HbClientConfig& config);

    bool isValid() const;

    virtual void setReconnectionDelay(quint16 duration);
    virtual quint16 reconnectionDelay() const;

private:
    quint16 mReconnectionDelay;
};
} // namespace network
} // namespace hb

using hb::network::HbClientConfig;

#endif // HBCLIENTCONFIG_H
