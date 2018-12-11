/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVERPEOPLEDCHANNEL_H
#define HBSERVERPEOPLEDCHANNEL_H

/*! \file HbServerPeopledChannel.h */

// Qt
#include <QtCore/QHash>
// Hb
// Local
#include <HbNetwork.h>
#include <listener/IHbUserListener.h>
#include <service/channel/HbServerChannel.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbServerPeopledChannel : public HbServerChannel, public IHbUserListener {
    Q_OBJECT

public:
    HbServerPeopledChannel() = default;
    virtual ~HbServerPeopledChannel() = default;

    virtual void internalReset(bool keep_uid = false) override;

    virtual void onUserConnected(ShConstHbNetworkUserInfo user_info) override;
    virtual void onUserDisconnected(ShConstHbNetworkUserInfo user_info) override;

    const QHash<QString, ShConstHbNetworkUserInfo>& connectedUsers() const;
    ShConstHbNetworkUserInfo connectedUser(const QString& email);

private:
    QHash<QString, ShConstHbNetworkUserInfo> mUsers;

signals:
    void userConnected(ShConstHbNetworkUserInfo user_info);
    void userDisconnected(ShConstHbNetworkUserInfo user_info);
};
} // namespace network
} // namespace hb

#endif // HBSERVERPEOPLEDCHANNEL_H
