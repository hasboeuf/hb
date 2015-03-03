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
            void onSocketContractToSend( networkuid receiver, HbNetworkContract * contract );
            void onUserContractToSend  ( const HbNetworkUserInfo & user_info, HbNetworkContract * contract );
            void onReadyContractToSend ( const HbNetworkContract * contract );
            void onUserToKick  ( const HbNetworkUserInfo &user_info, netwint reason, const QString & description );
            void onSocketToKick( networkuid socket_uid, netwint reason, const QString & description );

            // From HbAuthService.
            void onSocketAuthenticated  ( networkuid socket_uid, const HbNetworkUserInfo & user_info );
            void onSocketUnauthenticated( networkuid socket_uid, const QString reason );

            // From HbPresenceService
            void onSocketLagged( networkuid socket_uid, quint16 last_presence, quint16 kick_threshold );

        signals:
            void statusChanged( networkuid server_uid, HbNetworkProtocol::ServerStatus status );

        private:
            HbNetworkUser * isSocketAuthenticated( networkuid socket_uid );
            HbNetworkUser * getUser( const HbNetworkUserInfo & user_info );
            void kickUser  ( HbNetworkUser * user,  netwint reason, const QString & description );
            void kickSocket( networkuid socket_uid, netwint reason, const QString & description );

        private:
            networkuid mMainServer;
            QHash< networkuid, HbAbstractServer * > mServers;

            QSet < networkuid > mPendingSockets;
            QHash< networkuid, networkuid > mServerBySocketId;
            QHash< networkuid, HbNetworkUser * > mUserBySocketId;
            QHash< QString,    HbNetworkUser * > mUserByEmail;
        };
    }
}

#endif // HBSERVERCONNECTIONPOOL_H