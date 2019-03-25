#ifndef HBKICKCONTRACT_H
#define HBKICKCONTRACT_H

/*! \file HbKickContract.h */

// Qt
// Hb
#include <HbGlobal.h>
#include <contract/HbNetworkProtocol.h>
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkContract.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbKickContract : public HbNetworkContract {
public:
    HbKickContract();
    virtual ~HbKickContract() = default;
    HbKickContract(const HbKickContract& source);
    HbKickContract& operator=(const HbKickContract& source);

    virtual HbKickContract* create() const override;

    virtual bool read(QDataStream& stream) override;
    virtual bool write(QDataStream& stream) const override;

    void setReason(netwlint reason);
    void setDescription(const QString& description);

    netwlint reason() const;
    QString description() const;

private:
    netwlint mReason;
    QString mDescription;
};
} // namespace network
} // namespace hb

using hb::network::HbKickContract;

#endif // HBKICKCONTRACT_H
