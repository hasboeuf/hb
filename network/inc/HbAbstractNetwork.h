/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBABSTRACTNETWORK_H
#define HBABSTRACTNETWORK_H

// Qt
#include <QtNetwork/QAbstractSocket>
//#include <QtCore/QHash>
// Hb
#include <HbGlobal.h>
// Local
#include <HbNetwork.h>
#include <HbNetworkContract.h>
#include <HbNetworkConfig.h>

namespace hb
{
	namespace network
	{

		class IHbNetworkListener;

		class HB_NETWORK_DECL HbAbstractNetwork : public QObject
		{
			Q_OBJECT
			Q_DISABLE_COPY( HbAbstractNetwork )

		protected:
			inner class HB_NETWORK_DECL Exchanges final
			{
				Q_DISABLE_COPY(Exchanges)
				Q_FRIEND_CLASS(HbAbstractNetwork)

			public:

				Exchanges() = default;
				virtual ~Exchanges();

				template< typename T >
				inline T * plug()
				{
					T * reference = q_check_ptr(new T());
					HbNetworkContract * contract = q_dynamic_cast(HbNetworkContract *, reference);

					q_assert(contract->service() < HbNetworkContract::USER);
					return q_dynamic_cast(T *, add(contract));
				}

				template< typename T >
				inline void unplug()
				{
					T * reference = q_check_ptr(new T());
					remove(q_dynamic_cast(HbNetworkContract *, reference));
				}

				bool registered(HbNetworkContract::Service service,
					HbNetworkContract::Code code) const;

				HbNetworkContract * contract(HbNetworkContract::Service service,
					HbNetworkContract::Code code) const;

			private:

				HbNetworkContract * add(HbNetworkContract * contract);
				void remove(HbNetworkContract * contract);


			private:

				typedef QHash< HbNetworkContract::Code, HbNetworkContract * > Contracts;
				QHash< HbNetworkContract::Service, Contracts > _contracts;
			};

		public:

			virtual bool join() = 0;
			virtual bool leave() = 0;
			virtual bool ready() const = 0;

			//virtual void addListener(IHbNetworkListener * listener) final;
			//virtual void removeListener(IHbNetworkListener * listener) final;

			virtual bool send(const HbNetworkContract * contract) = 0;
			//virtual bool reply(int sender, const HbNetworkContract * contract) = 0;

			virtual QAbstractSocket::SocketError error() const final;
			virtual QString errorString() const final;

			//virtual const HbNetworkConfig & configuration() const = 0; SUB
			virtual const HbNetworkConfig & configuration() const;

		signals:
			void error(QAbstractSocket::SocketError error);

		protected:
			HbAbstractNetwork(QObject * parent = nullptr);
			virtual ~HbAbstractNetwork() = default;

			virtual Exchanges & exchanges() final;
			virtual const Exchanges & exchanges() const final;

			//virtual const QList< IHbNetworkListener * > & listeners() const final;

			virtual void raiseError(QAbstractSocket::SocketError error, const QString & message) final;

		private:
			HbNetworkConfig _config; // SUB
			Exchanges _exchanges;
			//QList< IHbNetworkListener * > _listeners;

			QAbstractSocket::SocketError _errorCode;
			QString _errorString;

		};
	}
}

#endif // HBABSTRACTNETWORK_H
