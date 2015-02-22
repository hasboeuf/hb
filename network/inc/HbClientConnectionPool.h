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
#include <user/HbNetworkUserInfo.h>

namespace hb
{
    namespace network
    {
        class HbAbstractClient;

        class HB_NETWORK_DECL HbClientConnectionPool: public HbConnectionPool
        {
            Q_OBJECT
        public:

            HbClientConnectionPool();
            virtual ~HbClientConnectionPool();

            virtual bool leave();
            virtual bool setConfiguration( const HbGeneralClientConfig config );

            sockuid joinTcpClient( HbTcpClientConfig & config, bool main );

        public callbacks:
            // From HbAbstractClient.
            void onClientConnected       ( sockuid client_uid );
            void onClientDisconnected    ( sockuid client_uid );
            void onClientContractReceived( sockuid client_uid, const HbNetworkContract * contract );

            // From services.
            void onContractSent( const HbNetworkContract * contract );
            // From HbAuthService.
            void onUserConnected( sockuid client_uid, const HbNetworkUserInfo & user_info );

        private:
            sockuid mMainClient;
            QHash< sockuid, HbAbstractClient * > mClients;
            QHash< sockuid, netwuid > mClientBySocketId;
            HbNetworkUserInfo mUser; // TODO how to check if user is authenticated.
        };
    }
}

#endif // HBCLIENTCONNECTIONPOOL_H
