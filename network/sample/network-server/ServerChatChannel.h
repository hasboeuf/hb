#ifndef SERVERCHATCHANNEL_H
#define SERVERCHATCHANNEL_H

/*! \file HbServerPeopledChannel.h */

// Qt
// Hb
#include <service/channel/HbServerPeopledChannel.h>
// Local

namespace hb {
namespace networkexample {
/*!
 * TODOC
 */
class ServerChatChannel : public hb::network::HbServerPeopledChannel {
public:
    ServerChatChannel();
    virtual ~ServerChatChannel() = default;

    virtual void reset() override;
    virtual void plugContracts(HbNetworkExchanges& exchanges) override;
    virtual serviceuid uid() const override;

    virtual void onUserContractReceived(hb::network::ShConstHbNetworkUserInfo user_info,
                                        const HbNetworkContract* contract) override;
};
} // namespace networkexample
} // namespace hb

#endif // SERVERCHATCHANNEL_H
