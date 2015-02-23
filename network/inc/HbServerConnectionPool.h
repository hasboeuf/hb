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

            networkuid joinTcpServer( HbTcpServerConfig & config, bool main );

        public callbacks:
            // From HbAbstractServer.
            void onServerConnected       ( networkuid server_uid );
            void onServerDisconnected    ( networkuid server_uid );
            void onSocketConnected       ( networkuid server_uid, networkuid socket_uid );
            void onSocketDisconnected    ( networkuid server_uid, networkuid socket_uid );
            void onSocketContractReceived( networkuid server_uid, networkuid socket_uid, const HbNetworkContract * contract );

            // From services.
            void onContractSent( const HbNetworkContract * contract );
            void onContractSent( networkuid socket_uid, const HbNetworkContract * contract ); // TODO useless ???
            void onUserKick    ( const HbNetworkUser & user_info, netwint reason );
            void onSocketKick  ( networkuid socket_uid, netwint reason );

            // From HbAuthService.
            void onUserConnected( networkuid socket_id, const HbNetworkUserInfo & user_info );

        signals:
            void statusChanged( networkuid server_uid, HbNetworkProtocol::ServerStatus status );

        private:
            HbNetworkUser * isSocketAuthenticated( networkuid socket_uid );

        private:
            networkuid mMainServer;
            QHash< networkuid, HbAbstractServer * > mServers;

            QSet < networkuid > mPendingSockets;
            QHash< networkuid, networkuid > mServerBySocketId;
            QHash< networkuid, HbNetworkUser * > mUserBySocketId;
        };
    }
}

#endif // HBSERVERCONNECTIONPOOL_H
