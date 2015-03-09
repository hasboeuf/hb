/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVERPEOPLEDCHANNEL_H
#define HBSERVERPEOPLEDCHANNEL_H

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <service/channel/HbServerChannel.h>

namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL HbServerPeopledChannel : public HbServerChannel
        {
        public:

            HbServerPeopledChannel() = default;
            virtual ~HbServerPeopledChannel() = default;

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

#endif // HBSERVERPEOPLEDCHANNEL_H
