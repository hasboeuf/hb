#ifndef HBUSERSYNCCONTRACT_H
#define HBUSERSYNCCONTRACT_H

/*! \file HbUserConnectedContract.h */

// Qt
#include <QtCore/QObject>
#include <QtCore/QSet>
// Hb
#include <HbGlobal.h>
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkContract.h>
#include <user/HbNetworkUserSync.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbUserSyncContract : public HbNetworkContract {
public:
    HbUserSyncContract();
    virtual ~HbUserSyncContract() = default;
    HbUserSyncContract(const HbUserSyncContract& source);
    HbUserSyncContract& operator=(const HbUserSyncContract& source);

    virtual HbUserSyncContract* create() const override;

    void addSync(const HbNetworkUserSync& user_sync);
    const QList<HbNetworkUserSync>& syncs() const;

    virtual bool read(QDataStream& stream) override;
    virtual bool write(QDataStream& stream) const override;

private:
    QList<HbNetworkUserSync> mSyncs;
};
} // namespace network
} // namespace hb

using hb::network::HbUserSyncContract;

#endif // HBUSERSYNCCONTRACT_H
