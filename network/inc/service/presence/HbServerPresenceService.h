/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HbServerPresenceService_H
#define HbServerPresenceService_H

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <service/HbNetworkService.h>
#include <listener/IHbSocketListener.h>
#include <listener/IHbUserListener.h>

namespace hb
{
	namespace network
	{

        class HB_NETWORK_DECL HbServerPresenceService : public HbNetworkService, public IHbSocketListener, public IHbUserListener
		{
            Q_OBJECT

            Q_INTERFACES( hb::network::IHbSocketListener )
            Q_INTERFACES( hb::network::IHbUserListener )

		public:

            HbServerPresenceService();
            virtual ~HbServerPresenceService( ) = default;

            virtual HbNetworkProtocol::NetworkTypes enabledNetworkTypes() const;

        public callbacks:
            void onSocketConnected   ( sockuuid socket_uuid );
            void onSocketDisconnected( sockuuid socket_uuid );
            void onUserConnected   ( const HbNetworkUserInfo & user_info );
            void onUserDisconnected( const HbNetworkUserInfo & user_info );
            void onContractReceived( const HbNetworkContract * contract );
		};
	}
}

#endif // HbServerPresenceService_H
