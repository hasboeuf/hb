/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVERAUTHSERVICE_H
#define HBSERVERAUTHSERVICE_H

// Qt
// Hb
// Local
#include <service/auth/HbAuthService.h>
#include <user/HbNetworkUserInfo.h>
#include <config/service/auth/HbServiceAuthServerConfig.h>

class QTimerEvent;

namespace hb
{
    namespace network
    {

        class HbServerAuthStrategy;
        class HbAuthRequestContract;
        class HbAuthStatusContract;

        class HB_NETWORK_DECL HbServerAuthService : public HbAuthService
        {
            Q_OBJECT

        public:

            HbServerAuthService();
            virtual ~HbServerAuthService();

            const HbServiceAuthServerConfig & config() const;
            void setConfig( const HbServiceAuthServerConfig & config );

        private:
            void timerEvent( QTimerEvent * event );
            bool checkSocket( sockuid socket_uid );
            void addSocket  ( sockuid socket_uid );
            void delSocket  ( sockuid socket_uid, bool delete_responses = true );
            void kickSocket ( sockuid socket_uid, HbNetworkProtocol::KickCode reason );

        public callbacks:
            // From HbConnectionPool.
            virtual void onContractReceived( const HbNetworkContract * contract );
            virtual void onSocketConnected   ( sockuid socket_uid );
            virtual void onSocketDisconnected( sockuid socket_uid );
            // From HbServerAuthStrategy.
            void onLoginSucceed( sockuid socket_uid, const HbNetworkUserInfo & user_info );
            void onLoginFailed ( sockuid socket_uid, HbNetworkProtocol::AuthStatus, const QString & description );

        signals:
            void userConnected( sockuid socket_id, const HbNetworkUserInfo & user_info );

        private:
            HbServiceAuthServerConfig mConfig;
            QHash< authstgy, HbServerAuthStrategy * > mStrategies;
            qint32 mTimerId;


            // InOut.
            QSet< sockuid >          mPendingSocket;
            QHash< sockuid, quint8 > mAuthTries;
            QHash< sockuid, quint8 > mAuthTimeout;
            QHash< sockuid, HbAuthStatusContract * > mResponses;
        };
    }
}

#endif // HBSERVERAUTHSERVICE_H
