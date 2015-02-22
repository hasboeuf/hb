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
#include <config/peer/HbGeneralConfig.h>
#include <config/com/HbTcpServerConfig.h>
#include <user/HbNetworkUserInfo.h>

namespace hb
{
    namespace network
    {
        class HbNetworkService;

        class HB_NETWORK_DECL HbConnectionPool: public QObject
        {
            Q_OBJECT
        public:

            HbConnectionPool() = default;
            virtual ~HbConnectionPool() = default;

            virtual bool leave() = 0;

        protected:
            virtual bool setConfiguration( const HbGeneralConfig config );
            void setExchanges( HbNetworkExchanges & exchanges );

        public callbacks:
            // From services.
            virtual void onContractSent( const HbNetworkContract * contract ) = 0;
            // From HbAuthService.
            virtual void onUserConnected( sockuid socket_id, const HbNetworkUserInfo & user_info ) = 0;

        signals:
            // To services.
            void socketConnected       ( sockuid socket_uid );
            void socketDisconnected    ( sockuid socket_uid );
            void socketContractReceived( const HbNetworkContract * contract );
            void userConnected         ( const HbNetworkUserInfo & user_info );
            void userDisconnected      ( const HbNetworkUserInfo & user_info );
            void userContractReceived  ( const HbNetworkUserInfo & user_info, const HbNetworkContract * contract );

        protected:
            virtual bool checkContractReceived( const HbNetworkContract * contract ); // TODO in /com ???

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

        protected:
            QHash< servuid, HbNetworkService * > mServices;
        };
    }
}

#endif // HBCONNECTIONPOOL_H
