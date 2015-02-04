/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HbClientPresenceService_H
#define HbClientPresenceService_H

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <service/HbNetworkService.h>

namespace hb
{
	namespace network
	{

        class HB_NETWORK_DECL HbClientPresenceService : public HbNetworkService
		{
            Q_OBJECT
		public:

            HbClientPresenceService() = default;
            virtual ~HbClientPresenceService( ) = default;

            virtual HbNetworkProtocol::NetworkTypes enabledNetworkTypes() const;

        public callbacks:
            void onContractReceived( const HbNetworkContract * contract );
		};
	}
}

#endif // HbClientPresenceService_H
