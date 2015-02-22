/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBPRESENCESERVICE_H
#define HBPRESENCESERVICE_H

// Qt
// Hb
// Local
#include <service/HbNetworkService.h>
#include <listener/IHbUserListener.h>

namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL HbPresenceService : public HbNetworkService, public IHbUserListener
        {
        public:

            HbPresenceService();
            virtual ~HbPresenceService() = default;
            virtual HbNetworkProtocol::NetworkTypes enabledNetworkTypes() const;
            virtual void plugContracts( HbNetworkExchanges & exchanges );            

        public callbacks:
            virtual void onUserConnected   ( const HbNetworkUserInfo & user_info ) = 0;
            virtual void onUserDisconnected( const HbNetworkUserInfo & user_info ) = 0;
            virtual void onContractReceived( const HbNetworkContract * contract  ) = 0;
        };
    }
}

#endif // HBPRESENCESERVICE_H
