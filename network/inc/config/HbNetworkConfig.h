/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNETWORKCONFIG_H
#define HBNETWORKCONFIG_H

// Qt
#include <QtCore/QIODevice>
// Hb
#include <HbGlobal.h>
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkExchanges.h>

namespace hb
{
	namespace network
	{
		class HB_NETWORK_DECL HbNetworkConfig
		{
		public:

			typedef struct final
			{
				qint16 connection;
				qint16 reconnection;
				qint16 disconnection;
			}
			Timeout;


		public:

			virtual void setTimeout(const Timeout & timeout);
			virtual void setOpenMode(QIODevice::OpenMode mode) final;

			virtual const Timeout & timeout() const final;
			virtual QIODevice::OpenMode openMode() const final;
			
            virtual const HbNetworkExchanges & exchanges() const final;
            virtual HbNetworkExchanges & exchanges() final;

			virtual bool isValid() const;

			HbNetworkConfig();
			HbNetworkConfig(const HbNetworkConfig & config);
			virtual ~HbNetworkConfig() = default;

			virtual HbNetworkConfig & operator =(const HbNetworkConfig & config);

        protected:
            HbNetworkExchanges mExchanges;

		private:
            Timeout mTimeout;
            QIODevice::OpenMode mOpenMode;

		};


	}
}

using hb::network::HbNetworkConfig;

#endif // HBNETWORKCONFIG_H
