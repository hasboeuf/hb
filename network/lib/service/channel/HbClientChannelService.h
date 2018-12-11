/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCLIENTCHANNELSERVICE_H
#define HBCLIENTCHANNELSERVICE_H

/*! \file HbClientChannelService.h */

// Qt
// Hb
#include <service/channel/HbClientChannel.h> // Covariance.
// Local
#include <HbNetwork.h>
#include <config/service/channel/HbServiceChannelClientConfig.h>
#include <listener/IHbClientUserContractListener.h>
#include <service/channel/HbChannelService.h>

namespace hb {
namespace network {

class HbClientPeopledChannel;

/*!
 * TODOC
 */
class HB_NETWORK_DECL HbClientChannelService : public HbChannelService, public IHbClientUserContractListener {
public:
    HbClientChannelService() = default;
    virtual ~HbClientChannelService() = default;

    virtual void reset() override;

    const HbServiceChannelClientConfig& config() const;
    void setConfig(const HbServiceChannelClientConfig& config);

    virtual bool plugChannel(HbNetworkChannel* channel, networkuid network_uid) override;
    virtual bool unplugChannel(HbNetworkChannel* channel) override;
    virtual HbClientChannel* channel(serviceuid channel_uid) override;

    void processContract(const HbNetworkContract* contract);

    virtual void onUserContractReceived(const HbNetworkContract* contract) override;
    virtual void onUserConnected(ShConstHbNetworkUserInfo user_info) override;
    virtual void onUserDisconnected(ShConstHbNetworkUserInfo user_info) override;

private:
    HbServiceChannelClientConfig mConfig;

    QHash<serviceuid, HbClientPeopledChannel*> mPeopledChannels;
};
} // namespace network
} // namespace hb

#endif // HBCLIENTCHANNELSERVICE_H
