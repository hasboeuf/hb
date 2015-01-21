/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HB_H
#define HB_H

// Qt
// Hb
// Local
#include <HbNetwork.h>

namespace hb
{
	namespace network
	{

		class HB_NETWORK_DECL Hb
		{
		public:

			Hb() = default;
			virtual ~Hb( ) = default;
		};
	}
}

#endif // HB_H
