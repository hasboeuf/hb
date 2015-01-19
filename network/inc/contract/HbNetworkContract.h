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


namespace hb
{
	namespace network
	{


		class HB_NETWORK_DECL HbNetworkContract
		{
			Q_GADGET
            Q_DISABLE_COPY( HbNetworkContract )
            Q_FRIEND_CLASS( HbNetworkExchanges )
            Q_FRIEND_CLASS( HbNetworkHeader )

		public:

            enum RoutingScheme : quint8
			{
                UNICAST = 0,
                MULTICAST = 1,
                BROADCAST = 2
			};

            enum Service : quint16
            {
                SERVICE_UNDEFINED = 0,
                SERVICE_UPDATE = 1,
                SERVICE_AUTH = 2,
                SERVICE_TIMEOUT = 3,

                SERVICE_USER = 255
            };

            enum Code : quint16
            {
                CODE_UNDEFINED = 0,
                CODE_CONNECTION_REQUEST = 1
            };


		public:

			virtual Service service() const final;
			virtual Code code() const final;

            virtual void setRouting( RoutingScheme routing );

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

			virtual bool read(QDataStream & stream) = 0;
			virtual bool write(QDataStream & stream) const = 0;

		protected:

			HbNetworkContract() = delete;
			HbNetworkContract(Service service, Code code);
			virtual ~HbNetworkContract() = default;

			virtual void reset();

		private:

			RoutingScheme routing() const;
			const QSet< quint16 > & receivers() const;


		private:

			Service _service;
			Code _code;

			RoutingScheme _routing;
			QSet< quint16 > _receivers;

			HbNetworkContract * _reply;
		};


	}
}

using hb::network::HbNetworkContract;

#endif // HBNETWORKCONTRACT_H
