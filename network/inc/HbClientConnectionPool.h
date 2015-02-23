/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCLIENTCONNECTIONPOOL_H
#define HBCLIENTCONNECTIONPOOL_H

// Qt
#include <QtCore/QHash>
// Hb
// Local
#include <HbNetwork.h>
#include <HbConnectionPool.h>
#include <config/peer/HbGeneralClientConfig.h>
#include <config/com/HbTcpClientConfig.h>
#include <user/HbNetworkUser.h>

namespace hb
{
    namespace link
    {
        class HbO2ClientFacebook;
    }
    namespace network
    {
        class HbAbstractClient;
        class HbClientAuthLoginObject;

        class HB_NETWORK_DECL HbClientConnectionPool: public HbConnectionPool
        {
            Q_OBJECT
        public:

            HbClientConnectionPool() = delete;
            HbClientConnectionPool( const HbGeneralClientConfig & config );
            virtual ~HbClientConnectionPool();

            virtual bool leave();
            networkuid joinTcpClient( HbTcpClientConfig & config, bool main );
            bool authRequest( HbClientAuthLoginObject * login_object );

        public callbacks:
            // From HbAbstractClient.
            void onClientConnected       ( networkuid client_uid );
            void onClientDisconnected    ( networkuid client_uid );
            void onClientContractReceived( networkuid client_uid, const HbNetworkContract * contract );

            // From services.
            void onContractSent( const HbNetworkContract * contract );
            // From HbAuthService.
            void onUserConnected( networkuid client_uid, const HbNetworkUserInfo & user_info );

            // From HbNetworkUser.
            void onMeStatusChanged( HbNetworkProtocol::UserStatus status );

        signals:
            void statusChanged( networkuid client_uid, HbNetworkProtocol::ClientStatus status );
            void meStatusChanged( HbNetworkProtocol::UserStatus status );

        private:
            QHash< networkuid, HbAbstractClient * > mClients;
            QHash< networkuid, networkuid > mClientBySocketId;
            HbNetworkUser mUser;
        };
    }
}

#endif // HBCLIENTCONNECTIONPOOL_H
