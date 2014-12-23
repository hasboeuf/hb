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

            virtual void receive( int sender, const HbNetworkContract * contract ) = 0;
    
        protected :

            virtual ~IHbNetworkListener() = default;
		};

	}
}

using hb::network::IHbNetworkListener;

#endif // IHBNETWORKLISTENER_H
