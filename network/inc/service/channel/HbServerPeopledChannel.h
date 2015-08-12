/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVERPEOPLEDCHANNEL_H
#define HBSERVERPEOPLEDCHANNEL_H

/*! \file HbServerPeopledChannel.h */

// Qt
#include <QtCore/QHash>
// Hb
// Local
#include <HbNetwork.h>
#include <service/channel/HbServerChannel.h>
#include <listener/IHbUserListener.h>

namespace hb
{
    namespace network
    {
        /*!
         * TODOC
         */
        class HB_NETWORK_DECL HbServerPeopledChannel : public HbServerChannel, public IHbUserListener
        {
            Q_OBJECT

        public:

            HbServerPeopledChannel() = default;
            virtual ~HbServerPeopledChannel() = default;

            virtual void onUserConnected   ( const HbNetworkUserData & user_data ) override final;
            virtual void onUserDisconnected( const HbNetworkUserData & user_data ) override final;

        public callbacks:

        private:
            QHash< QString, HbNetworkUserData > mUsers;

        signals:
            void userConnected   ( const HbNetworkUserInfo & user_info );
            void userDisconnected( const HbNetworkUserInfo & user_info );

        };
    }
}

#endif // HBSERVERPEOPLEDCHANNEL_H
