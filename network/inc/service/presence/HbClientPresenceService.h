/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCLIENTPRESENCESERVICE_H
#define HBCLIENTPRESENCESERVICE_H

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <service/presence/HbPresenceService.h>
#include <config/service/presence/HbServicePresenceClientConfig.h>

namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL HbClientPresenceService : public HbPresenceService
        {
            Q_OBJECT

        public:

            HbClientPresenceService() = default;
            virtual ~HbClientPresenceService( ) = default;

            const HbServicePresenceClientConfig & config() const;
            void setConfig( const HbServicePresenceClientConfig & config );

        public callbacks:
            void onUserConnected   ( const HbNetworkUserInfo & user_info );
            void onUserDisconnected( const HbNetworkUserInfo & user_info );
            void onContractReceived( const HbNetworkContract * contract );

        private:
            HbServicePresenceClientConfig mConfig;
        };
    }
}

#endif // HBCLIENTPRESENCESERVICE_H
