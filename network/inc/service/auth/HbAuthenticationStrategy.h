/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBAUTHENTICATIONSTRATEGY_H
#define HBAUTHENTICATIONSTRATEGY_H

// Qt
// Hb
#include <listener/IHbSocketListener.h>
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkProtocol.h>
#include <contract/HbConnectionContract.h>

namespace hb
{
	namespace network
	{

        class HB_NETWORK_DECL HbAuthenticationStrategy
		{
		public:

            HbAuthenticationStrategy() = default;
            virtual ~HbAuthenticationStrategy() = default;

            virtual HbNetworkProtocol::AuthenticationStatus tryLogin( const HbConnectionContract * contract ) = 0;

		};
	}
}

#endif // HBAUTHENTICATIONSTRATEGY_H
