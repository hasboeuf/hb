/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCLIENTCHANNELSERVICE_H
#define HBCLIENTCHANNELSERVICE_H

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <service/channel/HbChannelService.h>
#include <config/service/channel/HbServiceChannelClientConfig.h>

namespace hb
{
    namespace network
    {

        class HbClientChannel;

        class HB_NETWORK_DECL HbClientChannelService : public HbChannelService
        {
        public:

            HbClientChannelService() = default;
            virtual ~HbClientChannelService( ) = default;

            void plugContracts( HbNetworkExchanges & exchanges );

            const HbServiceChannelClientConfig & config() const;
            void setConfig( const HbServiceChannelClientConfig & config );

        public callbacks:
            virtual void onContractReceived( const HbNetworkContract * contract  );
            virtual void onUserConnected   ( const HbNetworkUserInfo & user_info );
            virtual void onUserDisconnected( const HbNetworkUserInfo & user_info );

        private:
            HbServiceChannelClientConfig mConfig;

            QHash< serviceuid, HbClientChannel * > mChannels;

        };
    }
}

#endif // HBCLIENTCHANNELSERVICE_H
