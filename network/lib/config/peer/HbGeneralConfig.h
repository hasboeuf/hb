#ifndef HBGENERALCONFIG_H
#define HBGENERALCONFIG_H

/*! \file HbGeneralConfig.h */

// Qt
#include <QtCore/QHash>
#include <QtCore/QString>
// Hb
// Local
#include <HbNetwork.h>
#include <service/auth/HbServerAuthStrategy.h>
#include <service/channel/HbNetworkChannel.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbGeneralConfig {
public:
    HbGeneralConfig();
    HbGeneralConfig(const HbGeneralConfig& config);
    virtual ~HbGeneralConfig() = default;
    virtual HbGeneralConfig& operator=(const HbGeneralConfig& config);

    virtual bool isValid() const;

    QString appName() const;
    quint16 protocolVersion() const;

    void setAppName(const QString& app_name);
    void setProtocolVersion(quint16 protocol_version);

protected:
private:
    QString mAppName;
    quint16 mProtocolVersion;
};
} // namespace network
} // namespace hb

using hb::network::HbGeneralConfig;

#endif // HBGENERALCONFIG_H
