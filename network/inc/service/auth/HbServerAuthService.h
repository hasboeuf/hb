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
#include <HbNetwork.h>
#include <service/HbNetworkService.h>
#include <listener/IHbSocketListener.h>

namespace hb
{
	namespace network
	{

        class HbServerAuthStrategy;
        class HbAuthRequestContract;

        class HB_NETWORK_DECL HbServerAuthService : public HbNetworkService, public IHbSocketListener
		{
            Q_OBJECT

		public:

            HbServerAuthService();
            virtual ~HbServerAuthService() = default;

            virtual HbNetworkProtocol::NetworkTypes enabledNetworkTypes() const;

        public callbacks:
            virtual void onContractReceived( const HbNetworkContract * contract );
            virtual void onSocketConnected   ( sockuuid socket_uuid );
            virtual void onSocketDisconnected( sockuuid socket_uuid );

        private:
            bool tryFacebookLogin( const HbAuthRequestContract * contract );
        private:
            HbServerAuthStrategy * mpStrategy;
		};
	}
}

#endif // HBSERVERAUTHSERVICE_H
