/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVERCHANNEL_H
#define HBSERVERCHANNEL_H

/*! \file HbServerChannel.h */

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <service/channel/HbNetworkChannel.h>

namespace hb
{
    namespace network
    {
        /*!
         * TODOC
         */
        class HB_NETWORK_DECL HbServerChannel : public HbNetworkChannel
        {
        public:

            HbServerChannel() = default;
            virtual ~HbServerChannel() = default;

        public callbacks:

        };
    }
}

#endif // HBSERVERCHANNEL_H
