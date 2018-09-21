/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVERUSER_H
#define HBSERVERUSER_H

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
class HB_NETWORK_DECL HbServerUser : public HbNetworkUser {
    Q_OBJECT
public:
    HbServerUser();
    virtual ~HbServerUser() = default;

    void addSocket(networkuid server_uid, networkuid socket_uid, bool main = false);
    virtual void delSocket(networkuid socket_uid) override;

    networkuid socketUid(networkuid server_uid);
    virtual QList<networkuid> socketsUid() const override;

private:
    QHash<networkuid, networkuid> mSocketsByServer;
};
} // namespace network
} // namespace hb

#endif // HBSERVERUSER_H
