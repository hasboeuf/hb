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
// Local
#include <HbNetwork.h>
#include <service/channel/HbChannelService.h>
#include <config/service/channel/HbServiceChannelServerConfig.h>

namespace hb
{
    namespace network
    {

        class HbServerChannel;

        /*!
         * TODOC
         */
        class HB_NETWORK_DECL HbServerChannelService : public HbChannelService
        {
        public:

            HbServerChannelService() = default;
            virtual ~HbServerChannelService() = default;

            virtual void reset() override;

            void plugContracts( HbNetworkExchanges & exchanges ) override;

            const HbServiceChannelServerConfig & config() const;
            void setConfig( const HbServiceChannelServerConfig & config );

        public callbacks:
            virtual void onUserContractReceived( const HbNetworkUserInfo & user_info, const HbNetworkContract * contract ) override;
            virtual void onUserConnected   ( const HbNetworkUserInfo & user_info ) override;
            virtual void onUserDisconnected( const HbNetworkUserInfo & user_info ) override;

        private:
            HbServiceChannelServerConfig mConfig;

            QHash< serviceuid, HbServerChannel * > mChannels;
        };
    }
}

#endif // HBSERVERCHANNELSERVICE_H
