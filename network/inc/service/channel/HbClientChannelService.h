/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCLIENTCHANNELSERVICE_H
#define HBCLIENTCHANNELSERVICE_H

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

        class HB_NETWORK_DECL HbClientChannelService : public HbNetworkService
		{
		public:

            HbClientChannelService() = default;
            virtual ~HbClientChannelService( ) = default;

            virtual HbNetworkProtocol::NetworkTypes enabledNetworkTypes() const;

        public callbacks:
            virtual void onContractReceived( const HbNetworkContract * contract );
		};
	}
}

#endif // HBCLIENTCHANNELSERVICE_H
