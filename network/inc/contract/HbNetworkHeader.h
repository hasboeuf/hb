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
#include <contract/HbNetworkContract.h>

namespace hb
{
	namespace network
	{


		class HbNetworkHeader final
		{
			Q_DISABLE_COPY(HbNetworkHeader)

        public:

			HbNetworkHeader();
            HbNetworkHeader( quint16 sender );
            HbNetworkHeader( quint16 sender, const HbNetworkContract * contract );
			virtual ~HbNetworkHeader() = default;

			quint16 sender() const;

			HbNetworkContract::Service service() const;
			HbNetworkContract::Code code() const;

			HbNetworkContract::RoutingScheme routing() const;
			const QSet< quint16 > & receivers() const;

			friend QDataStream & operator <<(QDataStream & stream, const HbNetworkHeader & header);
			friend QDataStream & operator >>(QDataStream & stream, HbNetworkHeader & header);


		private:

			quint16 _sender;

			HbNetworkContract::Service _service;
			HbNetworkContract::Code _code;

			HbNetworkContract::RoutingScheme _routing;
			QSet< quint16 > _receivers;
		};


	}
}

#endif // HBNETWORKHEADER_H
