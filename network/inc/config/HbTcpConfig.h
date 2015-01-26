/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBTCPCONFIG_H
#define HBTCPCONFIG_H

// Qt
#include <QtNetwork/QHostAddress>
// Local
#include <config/HbNetworkConfig.h>


namespace hb
{
	namespace network
	{

        class HB_NETWORK_DECL HbTcpConfig
		{
		public:

			enum class SocketOption : qint16
			{
				NoOptions = 0,
				LowDelay = 1 << 0,
				KeepAlive = 1 << 1,
				MulticastLoopback = 1 << 2
			};
            Q_DECLARE_FLAGS( SocketOptions, SocketOption )

            void setAddress(const QString & address);
            void setAddress(const QHostAddress & address);
            void setPort   (quint16 port);
            void setOptions(SocketOptions options);

            const QHostAddress & address() const;
            quint16 port() const;
            SocketOptions options() const;



        protected:
			HbTcpConfig();
			HbTcpConfig(const HbTcpConfig & config);
			virtual ~HbTcpConfig() = default;
			HbTcpConfig & operator =(const HbTcpConfig & config);

            bool isValid() const;

		private:
            QHostAddress  mAddress;
            quint16       mPort;
            SocketOptions mOptions;
		};

	}
}

using hb::network::HbTcpConfig;

#endif // HBTCPCONFIG_H
