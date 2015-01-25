/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCONNECTIONPOOL_H
#define HBCONNECTIONPOOL_H

// Qt
#include <QtCore/QHash>
// Hb
// Local
#include <HbNetwork.h>
#include <config/HbTcpServerConfig.h>
#include <user/HbNetworkUserInfo.h>

namespace hb
{
	namespace network
	{
        class HbAbstractServer;
        class HbNetworkService;
        class HbNetworkUser;

        class HB_NETWORK_DECL HbConnectionPool: public QObject
		{
            Q_OBJECT
		public:

            HbConnectionPool();
            virtual ~HbConnectionPool();

            bool leave();
            quint16 joinTcpServer( const HbTcpServerConfig & config );

        public callbacks:
            // From HbAbstractServer.
            void onServerConnected       ( quint16 server_uuid );
            void onServerDisconnected    ( quint16 server_uuid );
            void onSocketConnected       ( quint16 server_uuid, quint32 socket_uuid );
            void onSocketDisconnected    ( quint16 server_uuid, quint32 socket_uuid );
            void onSocketContractReceived( quint16 server_uuid, quint16 socket_uuid, const HbNetworkContract * contract );

            // From HbNetworkService.

        signals:
            // To services.
            void socketConnected       ( quint16 socket_uuid );
            void socketDisconnected    ( quint16 socket_uuid );
            void socketContractReceived( const HbNetworkContract * contract );
            void userConnected         ( const HbNetworkUserInfo & user_info );
            void userDisconnected      ( const HbNetworkUserInfo & user_info );
            void userContractReceived  ( const HbNetworkUserInfo & user_info, const HbNetworkContract * contract );
            // To
            void socketPendingContractReceived( quint16 socket_uuid, const HbNetworkContract * contract );

        private:
            bool checkContractReceived( const HbNetworkContract * contract );

        private:
            QHash< quint16, HbAbstractServer * > mServers;
            QHash< quint16, HbNetworkService * > mServices;
            QHash< quint16, quint16 > mServerBySocketId;
            QHash< quint16, HbNetworkProtocol::NetworkType > mSocketTypes;
            QSet < quint16 > mPendingSockets;
            QHash< QString, HbNetworkUser * > mUserBySocketId;
		};
	}
}

#endif // HBCONNECTIONPOOL_H
