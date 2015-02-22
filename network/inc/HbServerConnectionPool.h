/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVERCONNECTIONPOOL_H
#define HBSERVERCONNECTIONPOOL_H

// Qt
#include <QtCore/QHash>
// Hb
// Local
#include <HbNetwork.h>
#include <HbConnectionPool.h>
#include <config/peer/HbGeneralServerConfig.h>
#include <config/com/HbTcpServerConfig.h>
#include <user/HbNetworkUserInfo.h>

namespace hb
{
    namespace network
    {
        class HbAbstractServer;
        class HbNetworkUser;

        class HB_NETWORK_DECL HbServerConnectionPool: public HbConnectionPool
        {
            Q_OBJECT
        public:

            HbServerConnectionPool() = delete;
            HbServerConnectionPool( const HbGeneralServerConfig & config );
            virtual ~HbServerConnectionPool();

            virtual bool leave();

            netwuid joinTcpServer( HbTcpServerConfig & config, bool main );

        public callbacks:
            // From HbAbstractServer.
            void onServerConnected       ( servuid server_uid );
            void onServerDisconnected    ( servuid server_uid );
            void onSocketConnected       ( servuid server_uid, sockuid socket_uid );
            void onSocketDisconnected    ( servuid server_uid, sockuid socket_uid );
            void onSocketContractReceived( servuid server_uid, sockuid socket_uid, const HbNetworkContract * contract );

            // From services.
            void onContractSent( const HbNetworkContract * contract );
            void onContractSent( sockuid socket_uid, const HbNetworkContract * contract ); // TODO useless ???
            void onUserKick    ( const HbNetworkUser & user_info, netwint reason );
            void onSocketKick  ( sockuid socket_uid, netwint reason );

            // From HbAuthService.
            void onUserConnected( sockuid socket_id, const HbNetworkUserInfo & user_info );

        private:
            HbNetworkUser * isSocketAuthenticated( sockuid socket_uid );

        private:
            netwuid mMainServer;
            QHash< netwuid, HbAbstractServer * > mServers;

            QSet < sockuid > mPendingSockets;
            QHash< sockuid, netwuid > mServerBySocketId;
            QHash< sockuid, HbNetworkUser * > mUserBySocketId;
        };
    }
}

#endif // HBSERVERCONNECTIONPOOL_H
