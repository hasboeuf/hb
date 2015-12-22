/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef SERVERCHATCHANNEL_H
#define SERVERCHATCHANNEL_H

/*! \file HbServerPeopledChannel.h */

// Qt
// Hb
#include <service/channel/HbServerPeopledChannel.h>
// Local

namespace hb
{
    namespace networkexample
    {
        /*!
         * TODOC
         */
        class ServerChatChannel : public hb::network::HbServerPeopledChannel
        {
        public:

            ServerChatChannel();
            virtual ~ServerChatChannel() = default;

            virtual void reset() override;
            virtual void plugContracts( HbNetworkExchanges & exchanges ) override;
            virtual serviceuid uid() const override;

        public callbacks:
            virtual void onUserContractReceived( hb::network::ShConstHbNetworkUserInfo user_info, const HbNetworkContract * contract ) override;
        };
    }
}

#endif // SERVERCHATCHANNEL_H
