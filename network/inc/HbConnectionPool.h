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
#include <config/com/HbTcpServerConfig.h>
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
            void onServerConnected       ( servuuid server_uuid );
            void onServerDisconnected    ( servuuid server_uuid );
            void onSocketConnected       ( servuuid server_uuid, sockuuid socket_uuid );
            void onSocketDisconnected    ( servuuid server_uuid, sockuuid socket_uuid );
            void onSocketContractReceived( servuuid server_uuid, sockuuid socket_uuid, const HbNetworkContract * contract );

            // From services.
            void onContractSent( const HbNetworkContract * contract );
            void onContractSent( sockuuid socket_uuid, const HbNetworkContract * contract );
            void onUserKick    ( const HbNetworkUser & user_info, kickcode reason );
            void onSocketKick  ( sockuuid socket_uuid, kickcode reason );

            // From HbAuthService.
            void onNewUserConnected( sockuuid socket_id, const HbNetworkUserInfo & user_info );
            // From HbPresenceService.
            void onUserWaited();



        signals:
            // To services.
            void socketConnected       ( sockuuid socket_uuid );
            void socketDisconnected    ( sockuuid socket_uuid );
            void socketContractReceived( const HbNetworkContract * contract );
            void userConnected         ( const HbNetworkUserInfo & user_info );
            void userDisconnected      ( const HbNetworkUserInfo & user_info );
            void userContractReceived  ( const HbNetworkUserInfo & user_info, const HbNetworkContract * contract );

        private:
            bool checkContractReceived( const HbNetworkContract * contract );
            HbNetworkUser * isSocketAuthenticated( sockuuid socket_uuid );

            template< class T >
            QList< T * > getListeners()
            {
                QList< T * > listeners;
                foreach( HbNetworkService * service, mServices )
                {
                    T * listener = dynamic_cast< T * >( service );
                    if( listener )
                    {
                        listeners.push_back( listener );
                    }
                }

                return listeners;
            }

        private:
            QHash< netwuuid, HbAbstractServer * > mServers;
            QHash< servuuid, HbNetworkService * > mServices;

            QSet < sockuuid > mPendingSockets;
            QHash< sockuuid, netwuuid > mServerBySocketId;
            QHash< sockuuid, HbNetworkUser * > mUserBySocketId;
		};
	}
}

#endif // HBCONNECTIONPOOL_H
