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
#include <HbNetwork.h>

namespace hb
{
	namespace network
	{
        // TODO remove decl

        class HB_NETWORK_DECL HbNetworkHeader final
		{
            Q_DISABLE_COPY( HbNetworkHeader )

        public:

			HbNetworkHeader();
            HbNetworkHeader( quint16 sender );
            HbNetworkHeader( quint16 sender, const HbNetworkContract * contract );
			virtual ~HbNetworkHeader() = default;

			quint16 sender() const;

            HbNetworkProtocol::Service service() const;
            HbNetworkProtocol::Code code() const;

            HbNetworkProtocol::RoutingScheme routing() const;
			const QSet< quint16 > & receivers() const;

            friend QDataStream & operator<<( QDataStream & stream, const HbNetworkHeader & header );
            friend QDataStream & operator>>( QDataStream & stream, HbNetworkHeader & header );


		private:

			quint16 _sender;

            HbNetworkProtocol::Service _service;
            HbNetworkProtocol::Code _code;

            HbNetworkProtocol::RoutingScheme _routing;
			QSet< quint16 > _receivers;
		};

        HB_NETWORK_DECL QDataStream & operator<<(QDataStream & stream, const HbNetworkHeader & header);
        HB_NETWORK_DECL QDataStream & operator>>(QDataStream & stream, HbNetworkHeader & header);
	}
}

#endif // HBNETWORKHEADER_H
