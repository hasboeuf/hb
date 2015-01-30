/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCLIENTTIMEOUTSERVICE_H
#define HBCLIENTTIMEOUTSERVICE_H

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

        class HB_NETWORK_DECL HbClientTimeoutService : public HbNetworkService
		{
		public:

            HbClientTimeoutService() = default;
            virtual ~HbClientTimeoutService( ) = default;

        public callbacks:
            void onContractReceived( const HbNetworkContract * contract );
		};
	}
}

#endif // HBCLIENTTIMEOUTSERVICE_H
