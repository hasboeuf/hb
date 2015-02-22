/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCLIENT_H
#define HBCLIENT_H

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <HbPeer.h>
#include <HbClientConnectionPool.h>
#include <config/peer/HbGeneralClientConfig.h>

namespace hb
{
    namespace network
    {
        class HB_NETWORK_DECL HbClient final : public HbPeer
        {
            Q_OBJECT
            Q_DISABLE_COPY( HbClient )
        public:

            HbClient() = delete;
            HbClient( const HbGeneralClientConfig & config );
            virtual ~HbClient() = default;

            networkuid joinTcpClient( HbTcpClientConfig & config, bool main );
            bool leave();

        private:
            HbClientConnectionPool mConnectionPool;

        };
    }
}

#endif // HBCLIENT_H
