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
#include <service/auth/HbServerAuthStrategy.h>
// Local


namespace hb
{
    namespace networkexample
	{

        class ServerAuthStrategy : public hb::network::HbServerAuthStrategy
		{
		public:

            ServerAuthStrategy() = default;
            virtual ~ServerAuthStrategy() = default;

            virtual HbNetworkProtocol::AuthStatus tryLogin( const HbAuthRequestContract * contract );

		};
	}
}

#endif // SERVERAUTHSTRATEGY_H
