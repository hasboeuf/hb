/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVER_H
#define HBSERVER_H

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <HbPeer.h>
#include <HbConnectionPool.h>
#include <config/peer/HbGeneralServerConfig.h>

namespace hb
{
    namespace network
    {
        class HbTcpServerConfig;
        class HbAbstractServer;

        class HB_NETWORK_DECL HbServer final : public HbPeer
        {
            Q_OBJECT
            Q_DISABLE_COPY( HbServer )
        public:

            HbServer() = delete;
            HbServer( const HbGeneralServerConfig & config );
            virtual ~HbServer() = default;

            quint16 joinTcpServer( const HbTcpServerConfig & config );
            bool leave();

        private:
            HbConnectionPool mConnectionPool;

        };
    }
}

#endif // HBSERVER_H
