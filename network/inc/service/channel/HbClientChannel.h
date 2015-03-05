/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCLIENTCHANNEL_H
#define HBCLIENTCHANNEL_H

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <service/channel/HbNetworkChannel.h>

namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL HbClientChannel : public HbNetworkChannel
        {
        public:

            HbClientChannel() = default;
            virtual ~HbNetworkChannel() = default;

            virtual HbNetworkProtocol::NetworkTypes enabledNetworkTypes() const = 0;
            virtual void plugContracts( HbNetworkExchanges & exchanges ) = 0;

            virtual void reset() = 0;

        public callbacks:
            virtual void onContractReceived( const HbNetworkContract * contract ) = 0;

        };
    }
}

#endif // HBCLIENTCHANNEL_H
