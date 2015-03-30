/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVICECHANNELCLIENTCONFIG_H
#define HBSERVICECHANNELCLIENTCONFIG_H

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <config/service/channel/HbServiceChannelConfig.h>

namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL HbServiceChannelClientConfig : public HbServiceChannelConfig
        {

        public:
            HbServiceChannelClientConfig();
            HbServiceChannelClientConfig( const HbServiceChannelClientConfig & config );
            virtual ~HbServiceChannelClientConfig(){} // = default; TODO linux-g++ issue
            virtual HbServiceChannelClientConfig & operator =( const HbServiceChannelClientConfig & config );

            virtual bool isValid() const;

        protected:

        private:

        };
    }
}

using hb::network::HbServiceChannelClientConfig;

#endif // HBSERVICECHANNELCLIENTCONFIG_H
