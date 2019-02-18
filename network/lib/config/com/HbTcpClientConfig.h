#ifndef HBTCPCLIENTCONFIG_H
#define HBTCPCLIENTCONFIG_H

/*! \file HbTcpClientConfig.h */

// Qt
#include <QtNetwork/QHostAddress>
// Local
#include <config/com/HbClientConfig.h>
#include <config/com/HbTcpConfig.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbTcpClientConfig : public virtual HbNetworkConfig, public HbTcpConfig, public HbClientConfig {
public:
    HbTcpClientConfig() = default;
    virtual ~HbTcpClientConfig() = default;
    HbTcpClientConfig(const HbTcpClientConfig& config);
    HbTcpClientConfig& operator=(const HbTcpClientConfig& config);

    bool isValid() const;
};
} // namespace network
} // namespace hb

using hb::network::HbTcpClientConfig;

#endif // HBTCPSERVERCONFIG_H
