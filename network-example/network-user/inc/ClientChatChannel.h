/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef CLIENTCHATCHANNEL_H
#define CLIENTCHATCHANNEL_H

/*! \file ClientChatChannel.h */

// Qt
// Hb
#include <service/channel/HbClientPeopledChannel.h>
// Local

namespace hb
{
    namespace networkexample
    {
        /*!
         * TODOC
         */
        class ClientChatChannel : public hb::network::HbClientPeopledChannel
        {
        public:

            ClientChatChannel();
            virtual ~ClientChatChannel() = default;

            virtual void reset() override;

            virtual HbNetworkProtocol::NetworkTypes enabledNetworkTypes() const override;
            virtual void plugContracts( HbNetworkExchanges & exchanges ) override;

            virtual serviceuid uid() const override;

            virtual void onUserContractReceived( const HbNetworkUserData & user_data, const HbNetworkContract * contract ) override;

        public callbacks:

        };
    }
}

#endif // CLIENTCHATCHANNEL_H
