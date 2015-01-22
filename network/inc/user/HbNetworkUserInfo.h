/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNETWORKUSERINFO_H
#define HBNETWORKUSERINFO_H

// Qt
// Hb
// Local
#include <HbNetwork.h>

namespace hb
{
	namespace network
	{

        class HB_NETWORK_DECL HbNetworkUserInfo
		{
		public:

            HbNetworkUserInfo() = default;
            virtual ~HbNetworkUserInfo( ) = default;
		};
	}
}

#endif // HBNETWORKUSERINFO_H
