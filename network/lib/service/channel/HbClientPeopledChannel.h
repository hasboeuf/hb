#ifndef HBCLIENTPEOPLEDCHANNEL_H
#define HBCLIENTPEOPLEDCHANNEL_H

/*! \file HbClientPeopledChannel.h */

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <listener/IHbUserListener.h>
#include <service/channel/HbClientChannel.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbClientPeopledChannel : public HbClientChannel, public IHbUserListener {
    Q_OBJECT

public:
    HbClientPeopledChannel() = default;
    virtual ~HbClientPeopledChannel() = default;

    virtual void internalReset(bool keep_uid = false) override;

    virtual void onUserConnected(ShConstHbNetworkUserInfo user_info) override;
    virtual void onUserDisconnected(ShConstHbNetworkUserInfo user_info) override;

    const QHash<QString, ShConstHbNetworkUserInfo>& connectedUsers() const;

signals:
    void userConnected(ShConstHbNetworkUserInfo user_info);
    void userDisconnected(ShConstHbNetworkUserInfo user_info);

private:
    QHash<QString, ShConstHbNetworkUserInfo> mUsers;
};
} // namespace network
} // namespace hb

#endif // HBCLIENTPEOPLEDCHANNEL_H
