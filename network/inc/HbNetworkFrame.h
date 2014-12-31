/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNETWORKFRAME_H
#define HBNETWORKFRAME_H

// Local
#include <HbNetworkHeader.h>
#include <HbNetworkContract.h>

namespace hb
{
	namespace network
	{
		class HbNetworkFrame final
		{
			Q_DISABLE_COPY(HbNetworkFrame)

		public:
			HbNetworkFrame();
			virtual ~HbNetworkFrame() = default;

			friend QDataStream & operator <<(QDataStream & stream, const HbNetworkFrame & header);
			friend QDataStream & operator >>(QDataStream & stream, HbNetworkFrame & header);

		private:

		};


	}
}

#endif // HBNETWORKFRAME_H
