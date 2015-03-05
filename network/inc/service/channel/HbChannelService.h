/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCHANNELSERVICE_H
#define HBCHANNELSERVICE_H

// Qt
// Hb
// Local
#include <service/HbNetworkService.h>
#include <listener/IHbUserListener.h>

namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL HbChannelService : public HbNetworkService, public IHbUserListener
        {
        public:

            HbChannelService();
            virtual ~HbChannelService() = default;
            virtual HbNetworkProtocol::NetworkTypes enabledNetworkTypes() const;
            virtual void plugContracts( HbNetworkExchanges & exchanges ) = 0;

        public callbacks:
            virtual void onContractReceived( const HbNetworkContract * contract )  = 0;
            virtual void onUserConnected   ( const HbNetworkUserInfo & user_info ) = 0;
            virtual void onUserDisconnected( const HbNetworkUserInfo & user_info ) = 0;
        };
    }
}

#endif // HBCHANNELSERVICE_H
