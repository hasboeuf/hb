/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNETWORKSERVICE_H
#define HBNETWORKSERVICE_H

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkContract.h>
#include <listener/IHbContractListener.h>

namespace hb
{
	namespace network
	{

        class HB_NETWORK_DECL HbNetworkService : public IHbContractListener
		{
		public:

            HbNetworkService() = default;
            virtual ~HbNetworkService( ) = default;

            virtual void onContractReceived( const HbNetworkContract * contract ) = 0;

            virtual void id() const final
            {
                return mId;
            }

        protected:
            HbNetworkProtocol::Service mId = HbNetworkProtocol::SERVICE_UNDEFINED;
		};
	}
}

#endif // HBNETWORKSERVICE_H
