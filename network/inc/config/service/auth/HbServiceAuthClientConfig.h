/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVICEAUTHCLIENTCONFIG_H
#define HBSERVICEAUTHCLIENTCONFIG_H

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <config/service/auth/HbServiceAuthConfig.h>

namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL HbServiceAuthClientConfig : public HbServiceAuthConfig
        {

        public:
            HbServiceAuthClientConfig();
            HbServiceAuthClientConfig( const HbServiceAuthClientConfig & config );
            virtual ~HbServiceAuthClientConfig() = default;
            virtual HbServiceAuthClientConfig & operator =( const HbServiceAuthClientConfig & config );

            virtual bool isValid() const;

        protected:

        private:

        };
    }
}

using hb::network::HbServiceAuthClientConfig;

#endif // HBSERVICEAUTHCLIENTCONFIG_H
