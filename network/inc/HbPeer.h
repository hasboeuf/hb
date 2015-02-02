/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBPEER_H
#define HBPEER_H

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <config/peer/HbGeneralConfig.h>

namespace hb
{
	namespace network
	{

        class HB_NETWORK_DECL HbPeer
		{
            Q_DISABLE_COPY( HbPeer )

		public:

            HbPeer() = delete;
            HbPeer( const HbGeneralConfig & config );
            virtual ~HbPeer() = default;

            virtual bool isReady() const final;

        private:
            bool mReady;
		};
	}
}

#endif // HBSERVER_H
