/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef IHBCONTRACTLISTENER_H
#define IHBCONTRACTLISTENER_H

// Hb
#include <HbGlobal.h>
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkContract.h>

namespace hb
{
	namespace network
	{

        class HB_NETWORK_DECL IHbContractListener
		{

        public callbacks:
            virtual void onContractReceived( const HbNetworkContract * contract ) = 0;

        protected:
            virtual ~IHbContractListener() = default;
		};

	}
}

using hb::network::IHbContractListener;

#endif // IHBCONTRACTLISTENER_H
