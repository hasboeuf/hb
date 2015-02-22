/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVERPRESENCESERVICE_H
#define HBSERVERPRESENCESERVICE_H

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <service/presence/HbPresenceService.h>

namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL HbServerPresenceService : public HbPresenceService
        {
            Q_OBJECT

        public:

            HbServerPresenceService() = default;
            virtual ~HbServerPresenceService( ) = default;

        public callbacks:
            void onUserConnected   ( const HbNetworkUserInfo & user_info );
            void onUserDisconnected( const HbNetworkUserInfo & user_info );
            void onContractReceived( const HbNetworkContract * contract );
        };
    }
}

#endif // HBSERVERPRESENCESERVICE_H
