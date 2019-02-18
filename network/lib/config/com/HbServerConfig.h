#ifndef HBSERVERCONFIG_H
#define HBSERVERCONFIG_H

/*! \file HbServerConfig.h */

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
class HB_NETWORK_DECL HbServerConfig : public virtual HbNetworkConfig {
public:
    HbServerConfig();
    virtual ~HbServerConfig() = default;
    HbServerConfig(const HbServerConfig& config);
    HbServerConfig& operator=(const HbServerConfig& config);

    bool isValid() const;

    virtual void setMaxUsersPerThread(quint16 max_users);
    virtual quint16 maxUsersPerThread() const;
    virtual bool isThreaded() const;

private:
    quint16 mMaxUsersPerThread;
};
} // namespace network
} // namespace hb

using hb::network::HbServerConfig;

#endif // HBSERVERCONFIG_H
