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
#include <listener/IHbUserListener.h>

namespace hb
{
    namespace network
    {
        /*!
         * TODOC
         */
        class HB_NETWORK_DECL HbClientPeopledChannel :
            public HbClientChannel,
            public IHbUserListener
        {
            Q_OBJECT

        public:

            HbClientPeopledChannel() = default;
            virtual ~HbClientPeopledChannel() = default;

            virtual void onUserConnected   ( ShConstHbNetworkUserInfo user_info ) override final;
            virtual void onUserDisconnected( ShConstHbNetworkUserInfo user_info ) override final;

            const QHash< QString, ShConstHbNetworkUserInfo > & connectedUsers() const;

        public callbacks:

        signals:
            void userConnected   ( ShConstHbNetworkUserInfo user_info );
            void userDisconnected( ShConstHbNetworkUserInfo user_info );

        private:
            QHash< QString, ShConstHbNetworkUserInfo > mUsers;

        };
    }
}

#endif // HBCLIENTPEOPLEDCHANNEL_H
