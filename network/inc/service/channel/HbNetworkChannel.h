/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNETWORKCHANNEL_H
#define HBNETWORKCHANNEL_H

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <service/channel/HbChannelService.h>

namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL HbNetworkChannel : public HbChannelService
        {
        public:

            HbNetworkChannel() = default;
            virtual ~HbNetworkChannel() = default;

            virtual HbNetworkProtocol::NetworkTypes enabledNetworkTypes() const = 0;
            virtual void plugContracts( HbNetworkExchanges & exchanges ) = 0;

            virtual void reset() = 0;

        public callbacks:
            virtual void onUserContractReceived( const HbNetworkUserInfo & user_info, const HbNetworkContract * contract ) = 0;
            virtual void onUserConnected       ( const HbNetworkUserInfo & user_info ) = 0;
            virtual void onUserDisconnected    ( const HbNetworkUserInfo & user_info ) = 0;

        protected:

        };
    }
}

#endif // HBNETWORKCHANNEL_H
