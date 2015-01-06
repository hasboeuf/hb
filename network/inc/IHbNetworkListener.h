/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef IHBNETWORKLISTENER_H
#define IHBNETWORKLISTENER_H

// Hb
#include <HbGlobal.h>
#include <HbNetwork.h>

namespace hb
{
	namespace network
	{

		class HbNetworkContract;


		class HB_NETWORK_DECL IHbNetworkListener
		{
        public :

            virtual void receive( quint16 sender, const HbNetworkContract * contract ) = 0;
    
        protected :

            virtual ~IHbNetworkListener() = default;
		};

	}
}

using hb::network::IHbNetworkListener;

#endif // IHBNETWORKLISTENER_H
