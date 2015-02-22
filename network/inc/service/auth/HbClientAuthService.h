/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCLIENTAUTHSERVICE_H
#define HBCLIENTAUTHSERVICE_H

// Qt
// Hb
// Local
#include <service/auth/HbAuthService.h>
#include <config/service/auth/HbServiceAuthClientConfig.h>

namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL HbClientAuthService : public HbAuthService
        {
        public:

            HbClientAuthService() = default;
            virtual ~HbClientAuthService( ) = default;

            const HbServiceAuthClientConfig & config() const;
            void setConfig( const HbServiceAuthClientConfig & config );

        public callbacks:
            virtual void onContractReceived( const HbNetworkContract * contract );
            virtual void onSocketConnected   ( sockuid socket_uid );
            virtual void onSocketDisconnected( sockuid socket_uid );

        private:
            HbServiceAuthClientConfig mConfig;

        };
    }
}

#endif // HBCLIENTAUTHSERVICE_H
