/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCLIENTAUTHSERVICE_H
#define HBCLIENTAUTHSERVICE_H

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <service/HbNetworkService.h>

namespace hb
{
	namespace network
	{

        class HB_NETWORK_DECL HbClientAuthService : public HbNetworkService
		{
		public:

            HbClientAuthService() = default;
            virtual ~HbClientAuthService( ) = default;

        public callbacks:
            virtual void onContractReceived( const HbNetworkContract * contract );
		};
	}
}

#endif // HBCLIENTAUTHSERVICE_H
