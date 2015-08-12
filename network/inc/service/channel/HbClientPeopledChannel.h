/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCLIENTPEOPLEDCHANNEL_H
#define HBCLIENTPEOPLEDCHANNEL_H

/*! \file HbClientPeopledChannel.h */

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <service/channel/HbClientChannel.h>

namespace hb
{
    namespace network
    {
        /*!
         * TODOC
         */
        class HB_NETWORK_DECL HbClientPeopledChannel : public HbClientChannel
        {
        public:

            HbClientPeopledChannel() = default;
            virtual ~HbClientPeopledChannel() = default;

        public callbacks:

        private:
            QHash< QString, HbNetworkUserInfo > mUsers;


        };
    }
}

#endif // HBCLIENTPEOPLEDCHANNEL_H
