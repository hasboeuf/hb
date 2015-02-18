/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVICEPRESENCESERVERCONFIG_H
#define HBSERVICEPRESENCESERVERCONFIG_H

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <config/service/presence/HbServicePresenceConfig.h>

namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL HbServicePresenceServerConfig : public HbServicePresenceConfig
        {

        public:
            HbServicePresenceServerConfig();
            HbServicePresenceServerConfig( const HbServicePresenceServerConfig & config );
            virtual ~HbServicePresenceServerConfig() = default;
            virtual HbServicePresenceServerConfig & operator =( const HbServicePresenceServerConfig & config );

            virtual bool isValid() const;

        protected:

        private:

        };
    }
}

using hb::network::HbServicePresenceServerConfig;

#endif // HBSERVICEPRESENCESERVERCONFIG_H
