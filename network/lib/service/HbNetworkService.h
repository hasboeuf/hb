/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNETWORKSERVICE_H
#define HBNETWORKSERVICE_H

/*! \file HbNetworkService.h */

// Qt
#include <QtCore/QObject>
// Hb
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkContract.h>
#include <contract/HbNetworkExchanges.h>
#include <listener/IHbContractListener.h>
#include <user/HbNetworkUserInfo.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbNetworkService : public QObject {
    Q_OBJECT

public:
    HbNetworkService(QObject* parent = nullptr);
    virtual ~HbNetworkService() {
    } //!< \todo defaulted linux-g++ issue

    virtual void reset() = 0;
    virtual void plugContracts(HbNetworkExchanges& exchanges) = 0;

    virtual serviceuid uid() const = 0;

signals:
    void contractToSend(const HbNetworkContract* contract);

    // Server side.
    void userContractToSend(ShConstHbNetworkUserInfo user_info, HbNetworkContract* contract);
    void usersContractToSend(QList<ShConstHbNetworkUserInfo> users_info, HbNetworkContract* contract);
    void userToKick(ShConstHbNetworkUserInfo user_info, netwlint reason, const QString& description = QString());
    void socketToKick(networkuid socket_uid, netwlint reason, const QString& description = QString());
};
} // namespace network
} // namespace hb

#endif // HBNETWORKSERVICE_H
