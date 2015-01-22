/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCONNECTIONPOOL_H
#define HBCONNECTIONPOOL_H

// Qt
#include <QtCore/QHash>
// Hb
// Local
#include <HbNetwork.h>
#include <config/HbTcpServerConfig.h>

namespace hb
{
	namespace network
	{
        class HbAbstractServer;

        class HB_NETWORK_DECL HbConnectionPool
		{
		public:

            HbConnectionPool() = default;
            virtual ~HbConnectionPool();

            bool leave();
            quint16 joinTcpServer( const HbTcpServerConfig & config );

        private:
            QHash< quint16, HbAbstractServer * > mServers;
		};
	}
}

#endif // HBCONNECTIONPOOL_H
