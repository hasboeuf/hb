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
			Q_DISABLE_COPY(HbNetworkContract)
			Q_FRIEND_CLASS(HbAbstractNetwork)
			Q_FRIEND_CLASS(HbNetworkHeader)

		public:

			typedef quint16 Service;
			typedef quint16 Code;

			enum class RoutingScheme : qint16
			{
				Unicast = 0,
				Multicast = 1,
				Broadcast = 2
			};

		public:

			static const Service UNDEFINED = -1;
			static const Service USER = 255;
			static const Service MAXUSER = USHRT_MAX;

			static const Code UNKNOWN = -1;


		public:

			virtual Service service() const final;
			virtual Code code() const final;

			virtual void setRouting(RoutingScheme routing);

			virtual bool addReceiver(int receiver);
			virtual bool setReceiver(int receiver);
			virtual void resetReceivers();

			virtual bool setReply(HbNetworkContract * reply);
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
			const QSet< int > & receivers() const;


		private:

			Service _service;
			Code _code;

			RoutingScheme _routing;
			QSet< int > _receivers;

			HbNetworkContract * _reply;
		};


	}
}

using hb::network::HbNetworkContract;

#endif // HBNETWORKCONTRACT_H
