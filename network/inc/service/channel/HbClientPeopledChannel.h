/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCLIENTPEOPLEDCHANNEL_H
#define HBCLIENTPEOPLEDCHANNEL_H

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <service/channel/HbClientChannel.h>

namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL HbClientPeopledChannel : public HbClientChannel
        {
        public:

            HbClientPeopledChannel() = default;
            virtual ~HbClientPeopledChannel() = default;

            virtual HbNetworkProtocol::NetworkTypes enabledNetworkTypes() const = 0;
            virtual void plugContracts( HbNetworkExchanges & exchanges ) = 0;

            virtual void reset() = 0;

        public callbacks:
            virtual void onContractReceived( const HbNetworkContract * contract ) = 0;

        };
    }
}

#endif // HBCLIENTPEOPLEDCHANNEL_H
