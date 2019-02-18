#ifndef HBSERVERCHANNELSERVICE_H
#define HBSERVERCHANNELSERVICE_H

/*! \file HbServerChannelService.h */

// Qt
// Hb
#include <service/channel/HbServerChannel.h> // Covariance.
// Local
#include <HbNetwork.h>
#include <config/service/channel/HbServiceChannelServerConfig.h>
#include <listener/IHbServerUserContractListener.h>
#include <service/channel/HbChannelService.h>

namespace hb {
namespace network {

class HbServerPeopledChannel;

/*!
 * TODOC
 */
class HB_NETWORK_DECL HbServerChannelService : public HbChannelService, public IHbServerUserContractListener {
public:
    HbServerChannelService() = default;
    virtual ~HbServerChannelService() = default;

    virtual void reset() override;

    const HbServiceChannelServerConfig& config() const;
    void setConfig(const HbServiceChannelServerConfig& config);

    virtual bool plugChannel(HbNetworkChannel* channel, networkuid network_uid) override;
    virtual bool unplugChannel(HbNetworkChannel* channel) override;
    virtual HbServerChannel* channel(serviceuid channel_uid) override;

    // From HbConnectionPool.
    virtual void onUserContractReceived(ShConstHbNetworkUserInfo user_info, const HbNetworkContract* contract) override;
    virtual void onUserConnected(ShConstHbNetworkUserInfo user_info) override;
    virtual void onUserDisconnected(ShConstHbNetworkUserInfo user_info) override;

    // From channels.
    void onUserContractToSend(ShConstHbNetworkUserInfo user_info, HbNetworkContract* contract);
    void onUsersContractToSend(QList<ShConstHbNetworkUserInfo> users_info, HbNetworkContract* contract);
    void onUserToKick(ShConstHbNetworkUserInfo user_info, netwlint reason, const QString& description = QString());

private:
    HbServiceChannelServerConfig mConfig;
    QHash<serviceuid, HbServerPeopledChannel*> mPeopledChannels;
};
} // namespace network
} // namespace hb

#endif // HBSERVERCHANNELSERVICE_H
