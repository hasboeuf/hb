/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef CLIENTCHATCHANNEL_H
#define CLIENTCHATCHANNEL_H

/*! \file ClientChatChannel.h */

// Qt
// Hb
#include <service/channel/HbClientPeopledChannel.h>
// Local

namespace hb {
namespace networkexample {
/*!
 * TODOC
 */
class ClientChatChannel : public hb::network::HbClientPeopledChannel {
    Q_OBJECT

public:
    ClientChatChannel();
    virtual ~ClientChatChannel() = default;

    virtual void reset() override;
    virtual void plugContracts(HbNetworkExchanges& exchanges) override;
    virtual serviceuid uid() const override;

    void sendMessage(const QString message);

    virtual void onUserContractReceived(const HbNetworkContract* contract) override;

signals:
    void chatMessageReceived(const QString& author, const QString& message);
};
} // namespace networkexample
} // namespace hb

#endif // CLIENTCHATCHANNEL_H
