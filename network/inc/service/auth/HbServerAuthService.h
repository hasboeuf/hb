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

        public callbacks:
            // From HbConnectionPool.
            virtual void onContractReceived( const HbNetworkContract * contract );
            virtual void onSocketConnected   ( sockuuid socket_uuid );
            virtual void onSocketDisconnected( sockuuid socket_uuid );
            // From HbServerAuthStrategy.
            void onLoginSucceed( sockuuid sender, const HbNetworkUserInfo & user_info );
            void onLoginFailed ( sockuuid sender, HbNetworkProtocol::AuthStatus, const QString & description );

        private:
            QSet< sockuuid > mPendingSocket;
            QHash< authstgy, HbServerAuthStrategy * > mStrategies;
		};
	}
}

#endif // HBSERVERAUTHSERVICE_H
