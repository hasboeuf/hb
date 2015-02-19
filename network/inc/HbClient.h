/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCLIENT_H
#define HBCLIENT_H

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <HbPeer.h>
#include <config/peer/HbGeneralClientConfig.h>
#include <config/com/HbTcpClientConfig.h>

namespace hb
{
    namespace network
    {
        class HbAbstractClient;
        class HbNetworkService;

        class HB_NETWORK_DECL HbClient final : public HbPeer
        {
            Q_OBJECT
            Q_DISABLE_COPY( HbClient )
        public:

            HbClient() = delete;
            HbClient( const HbGeneralClientConfig & config );
            virtual ~HbClient() = default;

            bool leave();
            quint16 joinTcpClient( const HbTcpClientConfig & config );

        public callbacks:
            // From HbAbstractClient.
            void onClientConnected       ( sockuid client_uid );
            void onClientDisconnected    ( sockuid client_uid );
            void onClientContractReceived( sockuid client_uid, const HbNetworkContract * contract );

            // From services.
            void onContractSent( const HbNetworkContract * contract );

            // From HbAuthService.
            void onUserConnected   ( sockuid client_uid );
            void onUserDisconnected( sockuid client_uid );

        signals:
            // To services.
            void clientConnected       ( sockuid client_uid );
            void clientDisconnected    ( sockuid client_uid );
            void clientContractReceived( const HbNetworkContract * contract );
            void userConnected         ();
            void userDisconnected      ();
            void userContractReceived  ( const HbNetworkContract * contract );

        private:

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
            QHash< sockuid, HbAbstractClient * > mClients;
            QHash< servuid, HbNetworkService * > mServices;
        };
    }
}

#endif // HBCLIENT_H
