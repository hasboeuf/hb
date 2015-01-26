/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNETWORKAUTHENTICATIONSERVICE_H
#define HBNETWORKAUTHENTICATIONSERVICE_H

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

        class HB_NETWORK_DECL HbNetworkAuthenticationService : public HbNetworkService, public IHbSocketListener
		{
		public:

            HbNetworkAuthenticationService() = default;
            virtual ~HbNetworkAuthenticationService( ) = default;

        public callbacks:
            virtual void onContractReceived( const HbNetworkContract * contract );
            virtual void onSocketConnected   ( sockuuid socket_uuid );
            virtual void onSocketDisconnected( sockuuid socket_uuid );
		};
	}
}

#endif // HBNETWORKAUTHENTICATIONSERVICE_H
