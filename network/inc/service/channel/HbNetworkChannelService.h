/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNETWORKCHANNELSERVICE_H
#define HBNETWORKCHANNELSERVICE_H

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <service/HbNetworkService.h>
#include <listener/IHbUserListener.h>

namespace hb
{
	namespace network
	{

        class HB_NETWORK_DECL HbNetworkChannelService : public HbNetworkService, public IHbUserListener
		{
		public:

            HbNetworkChannelService() = default;
            virtual ~HbNetworkChannelService( ) = default;

        public callbacks:
            virtual void onContractReceived( const HbNetworkContract * contract );
            virtual void onUserConnected   ( const HbNetworkUserInfo & user_info );
            virtual void onUserDisconnected( const HbNetworkUserInfo & user_info );
		};
	}
}

#endif // HBNETWORKCHANNELSERVICE_H