/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCONNECTIONPOOL_H
#define HBCONNECTIONPOOL_H

/*! \file HbConnectionPool.h */

// Qt
#include <QtCore/QHash>
// Hb
// Local
#include <HbNetwork.h>
#include <config/peer/HbGeneralConfig.h>
#include <config/com/HbTcpServerConfig.h>
#include <user/HbNetworkUserData.h>

namespace hb
{
    namespace network
    {
        class HbNetworkService;

        /*!
         * TODOC
         */
        class HB_NETWORK_DECL HbConnectionPool: public QObject
        {
            Q_OBJECT
        public:

            HbConnectionPool() = delete;
            HbConnectionPool( const HbGeneralConfig & config );
            virtual ~HbConnectionPool() = default;

            virtual bool leave() = 0;
            virtual bool addChannel( HbNetworkChannel * channel ) final;

        protected:
            void setExchanges( HbNetworkExchanges & exchanges );

        public callbacks:
            // From services.
            virtual void onUserContractToSend ( const HbNetworkUserData & user_data, HbNetworkContract * contract ) = 0;
            virtual void onReadyContractToSend( const HbNetworkContract * contract ) = 0;
            // From HbAuthService.
            virtual void onSocketAuthenticated  ( networkuid socket_uid, const HbNetworkUserInfo & user_info ) = 0;
            virtual void onSocketUnauthenticated( networkuid socket_uid, quint8 try_number, quint8 max_tries, const QString & reason ) = 0;

        signals:
            // To services.
            void socketConnected       ( networkuid socket_uid );
            void socketDisconnected    ( networkuid socket_uid );
            void socketAuthenticated   ( const HbNetworkUserData & user_data );
            void socketUnauthenticated ( const HbNetworkUserData & user_data );
            void socketContractReceived( const HbNetworkContract * contract );
            void userConnected         ( const HbNetworkUserData & user_data );
            void userDisconnected      ( const HbNetworkUserData & user_data );
            void userContractReceived  ( const HbNetworkUserData & user_data, const HbNetworkContract * contract );

        protected:
            virtual void reset();

            HbNetworkService * getService( serviceuid service_uid );

            template< class T >
            T * getService( serviceuid service_uid )
            {
                return dynamic_cast< T * >( getService( service_uid ) );
            }

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
            bool mLeaving;
            QHash< serviceuid, HbNetworkService * > mServices;
        };
    }
}

#endif // HBCONNECTIONPOOL_H
