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
#include <user/HbNetworkUserInfo.h>

namespace hb
{
    namespace network
    {
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
            virtual bool plugChannel( HbNetworkChannel * channel, networkuid network_uid ) final;
            virtual bool unplugChannel( HbNetworkChannel * channel ) final;

        protected:
            void setExchanges( HbNetworkExchanges & exchanges );

        public callbacks:
            // From services.
            virtual void onContractToSend( const HbNetworkContract * contract ) = 0;
            // From HbAuthService.
            virtual void onSocketAuthenticated  ( networkuid socket_uid, const HbNetworkUserInfo & user_info ) = 0;
            virtual void onSocketUnauthenticated( networkuid socket_uid, quint8 try_number, quint8 max_tries, const QString & reason ) = 0;

        signals:
            // To services.
            void socketConnected       ( networkuid socket_uid );
            void socketDisconnected    ( networkuid socket_uid );
            void socketAuthenticated   ( networkuid socket_uid );
            void socketUnauthenticated ( networkuid socket_uid );
            void socketContractReceived( const HbNetworkContract * contract );
            void userConnected         ( ShConstHbNetworkUserInfo user_info );
            void userDisconnected      ( ShConstHbNetworkUserInfo user_info );
            void userContractReceived  ( ShConstHbNetworkUserInfo user_info, const HbNetworkContract * contract );

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
