/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVICEPRESENCECLIENTCONFIG_H
#define HBSERVICEPRESENCECLIENTCONFIG_H

/*! \file HbServicePresenceClientConfig.h */

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
            virtual ~HbServicePresenceClientConfig(){} //!< \todo defaulted linux-g++ issue
            virtual HbServicePresenceClientConfig & operator =( const HbServicePresenceClientConfig & config );

            virtual bool isValid() const;

            virtual void setKeepAliveInterval( quint16 interval ) final;
            virtual quint16 keepAliveInterval() const final;

        protected:

        private:
            quint16 mKeepAliveInterval;
        };
    }
}

using hb::network::HbServicePresenceClientConfig;

#endif // HBSERVICEPRESENCECLIENTCONFIG_H
