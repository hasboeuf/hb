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
            void onServerConnected       ( servuid server_uid );
            void onServerDisconnected    ( servuid server_uid );
            void onSocketConnected       ( servuid server_uid, sockuid socket_uid );
            void onSocketDisconnected    ( servuid server_uid, sockuid socket_uid );
            void onSocketContractReceived( servuid server_uid, sockuid socket_uid, const HbNetworkContract * contract );

            // From services.
            void onContractSent( const HbNetworkContract * contract );
            void onContractSent( sockuid socket_uid, const HbNetworkContract * contract );
            void onUserKick    ( const HbNetworkUser & user_info, kickcode reason );
            void onSocketKick  ( sockuid socket_uid, kickcode reason );

            // From HbAuthService.
            void onNewUserConnected( sockuid socket_id, const HbNetworkUserInfo & user_info );
            // From HbPresenceService.
            void onUserWaited();



        signals:
            // To services.
            void socketConnected       ( sockuid socket_uid );
            void socketDisconnected    ( sockuid socket_uid );
            void socketContractReceived( const HbNetworkContract * contract );
            void userConnected         ( const HbNetworkUserInfo & user_info );
            void userDisconnected      ( const HbNetworkUserInfo & user_info );
            void userContractReceived  ( const HbNetworkUserInfo & user_info, const HbNetworkContract * contract );

        private:
            bool checkContractReceived( const HbNetworkContract * contract );
            HbNetworkUser * isSocketAuthenticated( sockuid socket_uid );

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
            QHash< netwuid, HbAbstractServer * > mServers;
            QHash< servuid, HbNetworkService * > mServices;

            QSet < sockuid > mPendingSockets;
            QHash< sockuid, netwuid > mServerBySocketId;
            QHash< sockuid, HbNetworkUser * > mUserBySocketId;
        };
    }
}

#endif // HBCONNECTIONPOOL_H
