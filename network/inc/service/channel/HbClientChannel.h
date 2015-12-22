/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCLIENTCHANNEL_H
#define HBCLIENTCHANNEL_H

/*! \file HbClientChannel.h */

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <listener/IHbClientUserContractListener.h>
#include <service/channel/HbNetworkChannel.h>

namespace hb
{
    namespace network
    {
        /*!
         * TODOC
         */
        class HB_NETWORK_DECL HbClientChannel :
            public HbNetworkChannel,
            public IHbClientUserContractListener
        {
        public:

            HbClientChannel() = default;
            virtual ~HbClientChannel() = default;

            // Hide server side signals.
            void userContractToSend ( ShConstHbNetworkUserInfo user_info,             HbNetworkContract * contract )         = delete;
            void usersContractToSend( QList< ShConstHbNetworkUserInfo > users_infos,  HbNetworkContract * contract )         = delete;
            void userToKick  ( ShConstHbNetworkUserInfo user_info, netwint reason, const QString & description = QString() ) = delete;

        public callbacks:
            virtual void onContractToSend( HbNetworkContract * contract ) override;
        };
    }
}

#endif // HBCLIENTCHANNEL_H
