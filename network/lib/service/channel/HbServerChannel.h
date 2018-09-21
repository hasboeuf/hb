/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVERCHANNEL_H
#define HBSERVERCHANNEL_H

/*! \file HbServerChannel.h */

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <listener/IHbServerUserContractListener.h>
#include <service/channel/HbNetworkChannel.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbServerChannel : public HbNetworkChannel, public IHbServerUserContractListener {
public:
    HbServerChannel() = default;
    virtual ~HbServerChannel() = default;

private:
    // Hide low level signal, slot must be used by end user.
    using HbNetworkService::contractToSend;
    using HbNetworkService::userContractToSend;
    using HbNetworkService::usersContractToSend;
    using HbNetworkService::userToKick;

public
    callbacks : virtual void onContractToSend(HbNetworkContract* contract) override;
    void onUserContractToSend(ShConstHbNetworkUserInfo user_info, HbNetworkContract* contract);
    void onUsersContractToSend(QList<ShConstHbNetworkUserInfo> users_infos, HbNetworkContract* contract);
    void onUserToKick(ShConstHbNetworkUserInfo user_info, netwlint reason, const QString& description = QString());
};
} // namespace network
} // namespace hb

#endif // HBSERVERCHANNEL_H
