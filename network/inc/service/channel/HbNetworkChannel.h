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

namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL HbNetworkChannel
        {
        public:

            HbNetworkChannel();
            virtual ~HbNetworkChannel() = default;

            virtual servuuid uuid() const final;

            virtual void reset() = 0;

        protected:
            servuuid mUuid;

        };
    }
}

#endif // HBNETWORKCHANNEL_H
