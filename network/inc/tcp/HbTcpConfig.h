#ifndef HBTCPCONFIG_H
#define HBTCPCONFIG_H

// Qt
#include <QtNetwork/QHostAddress>
// Local
#include <HbNetworkConfig.h>


namespace hb
{
	namespace network
	{

		class HB_NETWORK_DECL HbTcpConfig : public virtual HbNetworkConfig
		{
		public:

			enum class SocketOption : qint16
			{
				NoOptions = 0,
				LowDelay = 1 << 0,
				KeepAlive = 1 << 1,
				MulticastLoopback = 1 << 2
			};
			Q_DECLARE_FLAGS(SocketOptions, SocketOption)

		public:

			HbTcpConfig();
			HbTcpConfig(const HbTcpConfig & config);
			virtual ~HbTcpConfig() = default;

			HbTcpConfig & operator =(const HbTcpConfig & config);

			void setTimeout(const Timeout & timeout);

			void setAddress(const QString & address);
			void setAddress(const QHostAddress & address);
			void setPort   (quint16 port);
			void setOptions(SocketOptions options);

			const QHostAddress & address() const;
			quint16 port() const;
			SocketOptions options() const;

			bool isValid() const;

		private:
			QHostAddress  _address;
			quint16       _port;
			SocketOptions _options;
		};

	}
}

using hb::network::HbTcpConfig;

#endif // HBTCPCONFIG_H
