#ifndef HBAUTHSTATUSCONTRACT_H
#define HBAUTHSTATUSCONTRACT_H

/*! \file HbAuthStatusContract.h */

// Qt
#include <QtCore/QObject>
#include <QtCore/QSet>
// Hb
#include <HbGlobal.h>
#include <contract/HbNetworkProtocol.h>
#include <user/HbNetworkUserInfo.h>
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkContract.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbAuthStatusContract : public HbNetworkContract {
public:
    HbAuthStatusContract();
    virtual ~HbAuthStatusContract() = default;
    HbAuthStatusContract(const HbAuthStatusContract& source);
    HbAuthStatusContract& operator=(const HbAuthStatusContract& source);

    virtual HbAuthStatusContract* create() const override;

    virtual bool read(QDataStream& stream) override;
    virtual bool write(QDataStream& stream) const override;

    void setUserInfo(const HbNetworkUserInfo& user_info);
    void setStatus(HbNetworkProtocol::AuthStatus status);
    void setDescription(const QString& description);
    void setTryNumber(quint8 try_number);
    void setMaxTries(quint8 max_tries);

    const HbNetworkUserInfo& userInfo() const;
    HbNetworkUserInfo& userInfo();
    HbNetworkProtocol::AuthStatus status() const;
    QString description() const;
    quint8 tryNumber() const;
    quint8 maxTries() const;

private:
    HbNetworkUserInfo mUserInfo;
    HbNetworkProtocol::AuthStatus mStatus;
    QString mDescription;
    quint8 mTryNumber;
    quint8 mMaxTries;
};
} // namespace network
} // namespace hb

using hb::network::HbAuthStatusContract;

#endif // HBAUTHSTATUSCONTRACT_H
