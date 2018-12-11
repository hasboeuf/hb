/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef SERVERSUMCHANNEL_H
#define SERVERSUMCHANNEL_H

/*! \file ServerSumChannel.h */

// Qt
// Hb
#include <service/channel/HbServerPeopledChannel.h>
// Local

namespace hb {
namespace networkexample {
/*!
 * TODOC
 */
class ServerSumChannel : public hb::network::HbServerChannel {
public:
    ServerSumChannel();
    virtual ~ServerSumChannel() = default;

    virtual void reset() override;
    virtual void plugContracts(HbNetworkExchanges& exchanges) override;
    virtual serviceuid uid() const override;

public:
    virtual void onUserContractReceived(hb::network::ShConstHbNetworkUserInfo user_info,
                                        const HbNetworkContract* contract) override;
};
} // namespace networkexample
} // namespace hb

#endif // SERVERSUMCHANNEL_H
