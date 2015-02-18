/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVICEPRESENCECLIENTCONFIG_H
#define HBSERVICEPRESENCECLIENTCONFIG_H

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <config/service/presence/HbServicePresenceConfig.h>

namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL HbServicePresenceClientConfig : public HbServicePresenceConfig
        {

        public:
            HbServicePresenceClientConfig();
            HbServicePresenceClientConfig( const HbServicePresenceClientConfig & config );
            virtual ~HbServicePresenceClientConfig() = default;
            virtual HbServicePresenceClientConfig & operator =( const HbServicePresenceClientConfig & config );

            virtual bool isValid() const;

        protected:

        private:

        };
    }
}

using hb::network::HbServicePresenceClientConfig;

#endif // HBSERVICEPRESENCECLIENTCONFIG_H
