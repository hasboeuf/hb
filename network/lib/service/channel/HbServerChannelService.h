/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVERCHANNELSERVICE_H
#define HBSERVERCHANNELSERVICE_H

/*! \file HbServerChannelService.h */

// Qt
// Hb
#include <service/channel/HbServerChannel.h> // Covariance.
// Local
#include <HbNetwork.h>
#include <listener/IHbServerUserContractListener.h>
#include <service/channel/HbChannelService.h>
#include <config/service/channel/HbServiceChannelServerConfig.h>

namespace hb
{
    namespace network
    {

        class HbServerPeopledChannel;

        /*!
         * TODOC
         */
        class HB_NETWORK_DECL HbServerChannelService : public HbChannelService, public IHbServerUserContractListener
        {
        public:

            HbServerChannelService() = default;
            virtual ~HbServerChannelService() = default;

            virtual void reset() override;

            const HbServiceChannelServerConfig & config() const;
            void setConfig( const HbServiceChannelServerConfig & config );

            virtual bool plugChannel(HbNetworkChannel * channel, networkuid network_uid ) override;
            virtual bool unplugChannel( HbNetworkChannel * channel ) override;
            virtual HbServerChannel * channel( serviceuid channel_uid ) override;

        public callbacks:
            // From HbConnectionPool.
            virtual void onUserContractReceived( ShConstHbNetworkUserInfo user_info, const HbNetworkContract * contract ) override;
            virtual void onUserConnected       ( ShConstHbNetworkUserInfo user_info ) override;
            virtual void onUserDisconnected    ( ShConstHbNetworkUserInfo user_info ) override;

            // From channels.
            void onUserContractToSend ( ShConstHbNetworkUserInfo user_info,             HbNetworkContract * contract );
            void onUsersContractToSend( QList< ShConstHbNetworkUserInfo > users_infos,  HbNetworkContract * contract );
            void onUserToKick( ShConstHbNetworkUserInfo user_info, netwlint reason, const QString & description = QString() );

        private:
            HbServiceChannelServerConfig mConfig;
            QHash< serviceuid, HbServerPeopledChannel * > mPeopledChannels;
        };
    }
}

#endif // HBSERVERCHANNELSERVICE_H
