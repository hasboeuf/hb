#ifndef HBCHANNELSERVICE_H
#define HBCHANNELSERVICE_H

/*! \file HbChannelService.h */

// Qt
#include <QtCore/QHash>
// Hb
// Local
#include <listener/IHbUserListener.h>
#include <service/HbNetworkService.h>

namespace hb {
namespace network {
class HbNetworkChannel;

/*!
 * TODOC
 */
class HB_NETWORK_DECL HbChannelService : public HbNetworkService, public IHbUserListener {
    Q_OBJECT
public:
    HbChannelService();
    virtual ~HbChannelService() = default;

    virtual void reset() override;
    virtual void plugContracts(HbNetworkExchanges& exchanges) override;
    virtual serviceuid uid() const override;

    virtual bool plugChannel(HbNetworkChannel* channel, networkuid network_uid);
    virtual bool unplugChannel(HbNetworkChannel* channel);
    virtual HbNetworkChannel* channel(serviceuid channel_uid);

    // From channels.
    void onContractToSend(const HbNetworkContract* contract);

signals:
    // To channels.
    void userConnected(ShConstHbNetworkUserInfo user_info);
    void userDisconnected(ShConstHbNetworkUserInfo user_info);

protected:
    QHash<serviceuid, HbNetworkChannel*> mChannels;
    QHash<QString, ShConstHbNetworkUserInfo> mUsers;
};
} // namespace network
} // namespace hb

#endif // HBCHANNELSERVICE_H
