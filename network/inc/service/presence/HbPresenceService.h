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
#include <listener/IHbSocketAuthListener.h>

namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL HbPresenceService : public HbNetworkService, public IHbSocketAuthListener
        {
        public:

            HbPresenceService();
            virtual ~HbPresenceService(){} // = default; TODO linux-g++ issue

            virtual void reset() = 0;
            virtual HbNetworkProtocol::NetworkTypes enabledNetworkTypes() const;
            virtual void plugContracts( HbNetworkExchanges & exchanges );            

        public callbacks:
            virtual void onSocketAuthenticated  ( networkuid socket_uid ) = 0;
            virtual void onSocketUnauthenticated( networkuid socket_uid ) = 0;
            virtual void onContractReceived( const HbNetworkContract * contract  ) = 0;
        };
    }
}

#endif // HBPRESENCESERVICE_H
