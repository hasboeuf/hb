/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVICEPRESENCECONFIG_H
#define HBSERVICEPRESENCECONFIG_H

/*! \file HbServicePresenceConfig.h */

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <config/service/HbServiceConfig.h>

namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL HbServicePresenceConfig : public HbServiceConfig
        {

        public:
            HbServicePresenceConfig();
            HbServicePresenceConfig( const HbServicePresenceConfig & config );
            virtual ~HbServicePresenceConfig(){} // = default; TODO linux-g++ issue
            virtual HbServicePresenceConfig & operator =( const HbServicePresenceConfig & config );

            virtual bool isValid() const;

        protected:

        private:

        };
    }
}

using hb::network::HbServicePresenceConfig;

#endif // HBSERVICEPRESENCECONFIG_H
