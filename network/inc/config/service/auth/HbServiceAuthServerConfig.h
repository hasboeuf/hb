/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVICEAUTHSERVERCONFIG_H
#define HBSERVICEAUTHSERVERCONFIG_H

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <config/service/auth/HbServiceAuthConfig.h>

namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL HbServiceAuthServerConfig : public HbServiceAuthConfig
        {

        public:
            HbServiceAuthServerConfig();
            HbServiceAuthServerConfig( const HbServiceAuthServerConfig & config );
            virtual ~HbServiceAuthServerConfig() = default;
            virtual HbServiceAuthServerConfig & operator =( const HbServiceAuthServerConfig & config );

            virtual bool isValid() const;

            virtual void setAuthMaxTries( quint16 max ) final;
            virtual quint16 authMaxTries() const;

            virtual void setAuthTimeout( quint16 timeout ) final;
            virtual quint16 authTimeout() const;

        protected:

        private:
            quint16 mAuthMaxTries;
            quint16 mAuthTimeout;
        };
    }
}

using hb::network::HbServiceAuthServerConfig;

#endif // HBSERVICEAUTHSERVERCONFIG_H
