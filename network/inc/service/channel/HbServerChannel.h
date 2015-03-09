/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVERCHANNEL_H
#define HBSERVERCHANNEL_H

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <service/channel/HbNetworkChannel.h>

namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL HbServerChannel : public HbNetworkChannel
        {
        public:

            HbServerChannel() = default;
            virtual ~HbServerChannel() = default;

            virtual HbNetworkProtocol::NetworkTypes enabledNetworkTypes() const = 0;
            virtual void plugContracts( HbNetworkExchanges & exchanges ) = 0;

            virtual void reset() = 0;

        public callbacks:
            virtual void onUserContractReceived( const HbNetworkUserInfo & user_info, const HbNetworkContract * contract ) = 0;
            virtual void onUserConnected       ( const HbNetworkUserInfo & user_info ) = 0;
            virtual void onUserDisconnected    ( const HbNetworkUserInfo & user_info ) = 0;

        };
    }
}

#endif // HBSERVERCHANNEL_H
