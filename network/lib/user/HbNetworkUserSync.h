#ifndef HBNETWORKUSERSYNC_H
#define HBNETWORKUSERSYNC_H

/*! \file HbNetworkUserSync.h */

// Qt
#include <QtCore/QObject>
#include <QtCore/QSet>
// Hb
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkProtocol.h>
#include <user/HbNetworkUserInfo.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbNetworkUserSync {
    friend QDataStream& operator<<(QDataStream& stream, const HbNetworkUserSync& user_sync);
    friend QDataStream& operator>>(QDataStream& stream, HbNetworkUserSync& user_sync);

public:
    HbNetworkUserSync();
    virtual ~HbNetworkUserSync() = default;
    HbNetworkUserSync(const HbNetworkUserSync& source);
    HbNetworkUserSync& operator=(const HbNetworkUserSync& source);

    const HbNetworkUserInfo& userInfo() const;
    void setUserInfo(ShConstHbNetworkUserInfo user_info);

    void setStatus(HbNetworkProtocol::NetworkUserStatus status);
    HbNetworkProtocol::NetworkUserStatus status() const;

private:
    HbNetworkUserInfo mUserInfo;
    HbNetworkProtocol::NetworkUserStatus mStatus;
};

QDataStream& operator<<(QDataStream& stream, const HbNetworkUserSync& user_sync);
QDataStream& operator>>(QDataStream& stream, HbNetworkUserSync& user_sync);
} // namespace network
} // namespace hb

using hb::network::HbNetworkUserSync;

#endif // HBNETWORKUSERSYNC_H
