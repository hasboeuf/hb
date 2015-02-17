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
#include <listener/IHbSocketListener.h>
#include <user/HbNetworkUserInfo.h>

class QTimerEvent;

namespace hb
{
	namespace network
	{

        class HbServerAuthStrategy;
        class HbAuthRequestContract;

        class HB_NETWORK_DECL HbServerAuthService : public HbAuthService, public IHbSocketListener
		{
            Q_OBJECT

		public:

            HbServerAuthService();
            virtual ~HbServerAuthService();

            virtual HbNetworkProtocol::NetworkTypes enabledNetworkTypes() const;

        private:
            void timerEvent( QTimerEvent * event );

        public callbacks:
            // From HbConnectionPool.
            virtual void onContractReceived( const HbNetworkContract * contract );
            virtual void onSocketConnected   ( sockuid socket_uid );
            virtual void onSocketDisconnected( sockuid socket_uid );
            // From HbServerAuthStrategy.
            void onLoginSucceed( sockuid sender, const HbNetworkUserInfo & user_info );
            void onLoginFailed ( sockuid sender, HbNetworkProtocol::AuthStatus, const QString & description );

        signals:
            void userConnected( sockuid socket_id, const HbNetworkUserInfo & user_info );

        private:
            QHash< authstgy, HbServerAuthStrategy * > mStrategies;
            qint32 mTimerId;


            // InOut.
            QSet< sockuid >          mPendingSocket;
            QHash< sockuid, quint8 > mAuthTries;
            QHash< sockuid, quint8 > mAuthTimeout;
        };
	}
}

#endif // HBSERVERAUTHSERVICE_H
