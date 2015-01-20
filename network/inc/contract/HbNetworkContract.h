/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNETWORKCONTRACT_H
#define HBNETWORKCONTRACT_H

// Qt
#include <QtCore/QObject>
#include <QtCore/QSet>
// Hb
#include <HbGlobal.h>
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkProtocol.h>

namespace hb
{
	namespace network
	{

		class HB_NETWORK_DECL HbNetworkContract
		{
			Q_GADGET
            Q_FRIEND_CLASS( HbNetworkExchanges )
            Q_FRIEND_CLASS( HbNetworkHeader )

		public:

            virtual HbNetworkProtocol::Service service() const final;
            virtual HbNetworkProtocol::Code code() const final;

            virtual void setRouting( HbNetworkProtocol::RoutingScheme routing );

            virtual bool addReceiver( quint16 receiver );
            virtual bool setReceiver( quint16 receiver );
			virtual void resetReceivers();

            virtual bool setReply( HbNetworkContract * reply );
			virtual HbNetworkContract * reply() const;

            template< typename T >
            inline T * value() const
			{
				return dynamic_cast< T * >(this);
			}

            virtual bool read( QDataStream & stream ) = 0;
            virtual bool write( QDataStream & stream ) const = 0;

		protected:

			HbNetworkContract() = delete;
            HbNetworkContract( HbNetworkProtocol::Service service, HbNetworkProtocol::Code code );
            HbNetworkContract( const HbNetworkContract & source );
            HbNetworkContract & operator=( const HbNetworkContract & source );
			virtual ~HbNetworkContract() = default;

            virtual HbNetworkContract * copy() const = 0;

		private:

            HbNetworkProtocol::RoutingScheme routing() const;
			const QSet< quint16 > & receivers() const;


		private:

            HbNetworkProtocol::Service _service;
            HbNetworkProtocol::Code _code;

            HbNetworkProtocol::RoutingScheme _routing;
			QSet< quint16 > _receivers;

			HbNetworkContract * _reply;
		};


	}
}

using hb::network::HbNetworkContract;

#endif // HBNETWORKCONTRACT_H
