#ifndef HBTCPCONFIG_H
#define HBTCPCONFIG_H

/*! \file HbTcpConfig.h */

// Qt
#include <QtNetwork/QHostAddress>
// Local
#include <config/com/HbNetworkConfig.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbTcpConfig : public virtual HbNetworkConfig {
public:
    enum class SocketOption : qint16 {
        NoOptions = 0,
        LowDelay = 1 << 0,
        KeepAlive = 1 << 1,
        MulticastLoopback = 1 << 2
    };
    Q_DECLARE_FLAGS(SocketOptions, SocketOption)

    HbTcpConfig();
    virtual ~HbTcpConfig() = default;
    HbTcpConfig(const HbTcpConfig& config);
    HbTcpConfig& operator=(const HbTcpConfig& config);

    bool isValid() const;

    void setAddress(const QString& address);
    void setAddress(const QHostAddress& address);
    void setPort(quint16 port);
    void setOptions(SocketOptions options);

    const QHostAddress& address() const;
    quint16 port() const;
    SocketOptions options() const;

private:
    QHostAddress mAddress;
    quint16 mPort;
    SocketOptions mOptions;
};

} // namespace network
} // namespace hb

using hb::network::HbTcpConfig;

#endif // HBTCPCONFIG_H
