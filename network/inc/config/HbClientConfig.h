/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCLIENTCONFIG_H
#define HBCLIENTCONFIG_H

// Qt
#include <QtCore/QtGlobal>
// Local
#include <HbNetwork.h>
#include <config/HbNetworkConfig.h>
#include <config/HbTimeoutClientConfig.h>

namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL HbClientConfig : public virtual HbNetworkConfig
        {

        public:

            HbClientConfig();
            HbClientConfig( const HbClientConfig & config );
            virtual ~HbClientConfig() = default;

            HbClientConfig & operator =( const HbClientConfig & config );

            bool isValid() const;

        private:
            HbTimeoutClientConfig mTimeout;
        };

    }
}

using hb::network::HbClientConfig;

#endif // HBCLIENTCONFIG_H
