/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVICECHANNELCONFIG_H
#define HBSERVICECHANNELCONFIG_H

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <config/service/HbServiceConfig.h>

namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL HbServiceChannelConfig : public HbServiceConfig
        {

        public:
            HbServiceChannelConfig();
            HbServiceChannelConfig( const HbServiceChannelConfig & config );
            virtual ~HbServiceChannelConfig(){} // = default; TODO linux-g++ issue
            virtual HbServiceChannelConfig & operator =( const HbServiceChannelConfig & config );

            virtual bool isValid() const;

        protected:

        private:

        };
    }
}

using hb::network::HbServiceChannelConfig;

#endif // HBSERVICECHANNELCONFIG_H
