/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVICEAUTHCLIENTCONFIG_H
#define HBSERVICEAUTHCLIENTCONFIG_H

/*! \file HbServiceAuthClientConfig.h */

// Qt
// Hb
#include <config/HbO2ClientConfig.h>
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

            void enableFacebookAuth( const hb::link::HbO2ClientConfig & config );
            const hb::link::HbO2ClientConfig & facebookAuthConfig() const;

            void enableGoogleAuth( const hb::link::HbO2ClientConfig & config );
            const hb::link::HbO2ClientConfig & googleAuthConfig() const;

        protected:

        private:
            hb::link::HbO2ClientConfig mFacebookAuthConfig;
            hb::link::HbO2ClientConfig mGoogleAuthConfig;
        };
    }
}

using hb::network::HbServiceAuthClientConfig;

#endif // HBSERVICEAUTHCLIENTCONFIG_H