/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCLIENTCHANNELSERVICE_H
#define HBCLIENTCHANNELSERVICE_H

/*! \file HbClientChannelService.h */

// Qt
// Hb
#include <service/channel/HbClientChannel.h> // Covariance.
// Local
#include <HbNetwork.h>
#include <service/channel/HbChannelService.h>
#include <config/service/channel/HbServiceChannelClientConfig.h>

namespace hb
{
    namespace network
    {

        /*!
         * TODOC
         */
        class HB_NETWORK_DECL HbClientChannelService : public HbChannelService
        {
        public:

            HbClientChannelService() = default;
            virtual ~HbClientChannelService( ) = default;

            virtual void reset() override;

            virtual void plugContracts( HbNetworkExchanges & exchanges ) override;

            const HbServiceChannelClientConfig & config() const;
            void setConfig( const HbServiceChannelClientConfig & config );

            virtual bool addChannel( HbNetworkChannel * channel ) override;
            virtual HbClientChannel * channel( serviceuid channel_uid ) override;

        public callbacks:
            virtual void onUserContractReceived( const HbNetworkUserData & user_data, const HbNetworkContract * contract ) override;
            virtual void onUserConnected       ( const HbNetworkUserData & user_data ) override;
            virtual void onUserDisconnected    ( const HbNetworkUserData & user_data ) override;

        private:
            HbServiceChannelClientConfig mConfig;

            QHash< serviceuid, HbClientChannel * > mChannels;

        };
    }
}

#endif // HBCLIENTCHANNELSERVICE_H
