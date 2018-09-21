/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVERCONNECTIONPOOL_H
#define HBSERVERCONNECTIONPOOL_H

/*! \file HbServerConnectionPool.h */

// Qt
#include <QtCore/QHash>
// Hb
// Local
#include <HbConnectionPool.h>
#include <HbNetwork.h>
#include <config/com/HbTcpServerConfig.h>
#include <config/peer/HbGeneralServerConfig.h>
#include <user/HbNetworkUserInfo.h>

namespace hb {
namespace network {
class HbAbstractServer;
class HbServerUser;

/*!
 * TODOC
 */
class HB_NETWORK_DECL HbServerConnectionPool : public HbConnectionPool {
    Q_OBJECT
public:
    HbServerConnectionPool() = delete;
    HbServerConnectionPool(const HbGeneralServerConfig& config);
    virtual ~HbServerConnectionPool();

    networkuid joinTcpServer(HbTcpServerConfig& config, bool main);
    virtual bool leave() override;

public
    callbacks :
        // From HbAbstractServer.
        void
        onServerConnected(networkuid server_uid);
    void onServerDisconnected(networkuid server_uid);
    void onSocketConnected(networkuid server_uid, networkuid socket_uid);
    void onSocketDisconnected(networkuid server_uid, networkuid socket_uid);
    void onSocketContractReceived(networkuid server_uid, networkuid socket_uid, const HbNetworkContract* contract);

    // From services.
    void onSocketContractToSend(networkuid receiver, HbNetworkContract* contract); //! \todo clean
    void onUsersContractToSend(QList<ShConstHbNetworkUserInfo> users_infos, HbNetworkContract* contract);
    void onUserContractToSend(ShConstHbNetworkUserInfo user_info, HbNetworkContract* contract);
    void onContractToSend(const HbNetworkContract* contract) override;
    void onUserToKick(ShConstHbNetworkUserInfo user_info, netwlint reason, const QString& description);
    void onSocketToKick(networkuid socket_uid, netwlint reason, const QString& description);

    // From HbAuthService.
    void onSocketAuthenticated(networkuid socket_uid, const HbNetworkUserInfo& user_info) override;
    void
    onSocketUnauthenticated(networkuid socket_uid, quint8 try_number, quint8 max_tries, const QString& reason) override;

    // From HbPresenceService
    void onSocketLagged(networkuid socket_uid, quint16 last_presence, quint16 kick_threshold);

signals:
    void statusChanged(networkuid server_uid, HbNetworkProtocol::ServerStatus status);

private:
    HbServerUser* isSocketAuthenticated(networkuid socket_uid);
    HbServerUser* getUser(ShConstHbNetworkUserInfo user_info);
    void kickUser(HbServerUser* user, netwlint reason, const QString& description);
    void kickSocket(networkuid socket_uid, netwlint reason, const QString& description);

private:
    networkuid mMainServer;
    QHash<networkuid, HbAbstractServer*> mServers;

    QSet<networkuid> mPendingSockets;
    QHash<networkuid, networkuid> mServerBySocketId;
    QHash<networkuid, HbServerUser*> mUserBySocketId;
    QHash<QString, HbServerUser*> mUserByEmail;
};
} // namespace network
} // namespace hb

#endif // HBSERVERCONNECTIONPOOL_H
