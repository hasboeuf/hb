#ifndef CLIENTSUMCHANNEL_H
#define CLIENTSUMCHANNEL_H

/*! \file ClientSumChannel.h */

// Qt
// Hb
#include <service/channel/HbClientChannel.h>
// Local

namespace hb {
namespace networkexample {
/*!
 * TODOC
 */
class ClientSumChannel : public hb::network::HbClientChannel {
    Q_OBJECT

public:
    ClientSumChannel();
    virtual ~ClientSumChannel() = default;

    virtual void reset() override;
    virtual void plugContracts(HbNetworkExchanges& exchanges) override;
    virtual serviceuid uid() const override;

    void requestSum(quint32 a, quint32 b);

    virtual void onUserContractReceived(const HbNetworkContract* contract) override;

signals:
    void computationReceived(qint32 result);
};
} // namespace networkexample
} // namespace hb

#endif // CLIENTSUMCHANNEL_H
