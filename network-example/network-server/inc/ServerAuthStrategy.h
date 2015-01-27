/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef SERVERAUTHSTRATEGY_H
#define SERVERAUTHSTRATEGY_H

// Qt
// Hb
#include <contract/HbNetworkProtocol.h>
#include <service/auth/HbNetworkAuthStrategy.h>
// Local


namespace hb
{
    namespace network
    {
        class HbConnectionContract;
    }

    namespace networkexample
	{

        class ServerAuthStrategy : public HbNetworkAuthStrategy
		{
		public:

            ServerAuthStrategy() = default;
            virtual ~ServerAuthStrategy() = default;

            virtual HbNetworkProtocol::AuthStatus tryLogin( const HbConnectionContract * contract );

		};
	}
}

#endif // SERVERAUTHSTRATEGY_H
