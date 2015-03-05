/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVERCHANNELSERVICE_H
#define HBSERVERCHANNELSERVICE_H

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

        class HB_NETWORK_DECL HbServerChannelService : public HbChannelService
        {
        public:

            HbServerChannelService() = default;
            virtual ~HbServerChannelService() = default;

            void plugContracts( HbNetworkExchanges & exchanges );

            const HbServiceChannelServerConfig & config() const;
            void setConfig( const HbServiceChannelServerConfig & config );

        public callbacks:
            virtual void onContractReceived( const HbNetworkContract * contract );
            virtual void onUserConnected   ( const HbNetworkUserInfo & user_info );
            virtual void onUserDisconnected( const HbNetworkUserInfo & user_info );

        private:
            HbServiceChannelServerConfig mConfig;
        };
    }
}

#endif // HBSERVERCHANNELSERVICE_H
