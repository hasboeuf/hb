/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBTCPCLIENTCONFIG_H
#define HBTCPCLIENTCONFIG_H

// Qt
#include <QtNetwork/QHostAddress>
// Local
#include <config/com/HbClientConfig.h>
#include <config/com/HbTcpConfig.h>


namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL HbTcpClientConfig final :
            public virtual HbNetworkConfig,
            public HbTcpConfig,
            public HbClientConfig
        {
        public:

            HbTcpClientConfig() = default;
            virtual ~HbTcpClientConfig() = default;
            HbTcpClientConfig( const HbTcpClientConfig & config );
            HbTcpClientConfig & operator =( const HbTcpClientConfig & config );

            bool isValid() const;

        };
    }
}

using hb::network::HbTcpClientConfig;

#endif // HBTCPSERVERCONFIG_H
