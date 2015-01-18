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

			virtual void setOwner( quint16 address ) final; // DEL
			virtual quint16 owner( ) const final; // DEL

			virtual void setTimeout(const Timeout & timeout);
			virtual void setOpenMode(QIODevice::OpenMode mode) final;

			virtual const Timeout & timeout() const final;
			virtual QIODevice::OpenMode openMode() const final;
			
			virtual int uuid() const final; // DEL

			virtual bool isValid() const;

			HbNetworkConfig();
			HbNetworkConfig(const HbNetworkConfig & config);
			virtual ~HbNetworkConfig() = default;

			virtual HbNetworkConfig & operator =(const HbNetworkConfig & config);


		private:
			quint16 _uuid; // DEL
			Timeout _timeout;
			QIODevice::OpenMode _openMode;
		};


	}
}

using hb::network::HbNetworkConfig;

#endif // HBNETWORKCONFIG_H
