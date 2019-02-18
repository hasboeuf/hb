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

    virtual void onUserContractReceived(hb::network::ShConstHbNetworkUserInfo user_info,
                                        const HbNetworkContract* contract) override;
};
} // namespace networkexample
} // namespace hb

#endif // SERVERSUMCHANNEL_H
