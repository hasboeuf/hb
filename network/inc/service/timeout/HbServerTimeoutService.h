/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVERTIMEOUTSERVICE_H
#define HBSERVERTIMEOUTSERVICE_H

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

        class HB_NETWORK_DECL HbServerTimeoutService : public HbNetworkService, public IHbSocketListener
		{
		public:

            HbServerTimeoutService() = default;
            virtual ~HbServerTimeoutService( ) = default;

        public callbacks:
            void onContractReceived( const HbNetworkContract * contract );
            void onSocketConnected   ( sockuuid socket_uuid );
            void onSocketDisconnected( sockuuid socket_uuid );
		};
	}
}

#endif // HBSERVERTIMEOUTSERVICE_H
