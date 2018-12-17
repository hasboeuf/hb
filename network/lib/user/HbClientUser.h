/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCLIENTUSER_H
#define HBCLIENTUSER_H

/*! \file HbNetworkUser.h */

// Qt
#include <QtCore/QObject>
#include <QtCore/QSet>
// Hb
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkProtocol.h>
#include <user/HbNetworkUser.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbClientUser : public HbNetworkUser {
    Q_OBJECT
public:
    HbClientUser(QObject* parent = nullptr);
    virtual ~HbClientUser() = default;

    virtual void reset();

    HbNetworkProtocol::UserStatus status() const;
    void setStatus(HbNetworkProtocol::UserStatus status);

    void addSocket(networkuid socket_uid, bool main = false);
    virtual void delSocket(networkuid socket_uid) override;
    virtual QList<networkuid> socketsUid() const override;

signals:
    void statusChanged(HbNetworkProtocol::UserStatus status);

private:
    HbNetworkProtocol::UserStatus mStatus;
    QList<networkuid> mSocketsUid;
};
} // namespace network
} // namespace hb

#endif // HBCLIENTUSER_H
