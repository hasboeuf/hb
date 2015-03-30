/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNETWORKCHANNEL_H
#define HBNETWORKCHANNEL_H

/*! \file HbNetworkChannel.h */

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <service/channel/HbChannelService.h>

namespace hb
{
    namespace network
    {
        /*!
         * TODOC
         */
        class HB_NETWORK_DECL HbNetworkChannel : public HbChannelService
        {
        public:

            HbNetworkChannel() = default;
            virtual ~HbNetworkChannel() = default;

        public callbacks:

        protected:

        };
    }
}

#endif // HBNETWORKCHANNEL_H
