/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNETWORKHEADER_H
#define HBNETWORKHEADER_H

// Local
#include <HbNetworkContract.h>

namespace hb
{
	namespace network
	{


		class HbNetworkHeader final
		{
			Q_DISABLE_COPY(HbNetworkHeader)

		public:

			static const HbNetworkContract::Code REGISTRATION = 0;


		public:

			HbNetworkHeader();
			HbNetworkHeader(int sender);
			HbNetworkHeader(int sender, const HbNetworkContract * contract);
			virtual ~HbNetworkHeader() = default;

			int sender() const;

			HbNetworkContract::Service service() const;
			HbNetworkContract::Code code() const;

			HbNetworkContract::RoutingScheme routing() const;
			const QSet< int > & receivers() const;

			friend QDataStream & operator <<(QDataStream & stream, const HbNetworkHeader & header);
			friend QDataStream & operator >>(QDataStream & stream, HbNetworkHeader & header);


		private:

			int _sender;

			HbNetworkContract::Service _service;
			HbNetworkContract::Code _code;

			HbNetworkContract::RoutingScheme _routing;
			QSet< int > _receivers;
		};


	}
}

#endif // HBNETWORKHEADER_H
