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

			virtual void setOwner(int address) final; // DEL
			virtual int owner() const final; // DEL

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
			int _uuid; // DEL
			Timeout _timeout;
			QIODevice::OpenMode _openMode;
		};


	}
}

using hb::network::HbNetworkConfig;

#endif // HBNETWORKCONFIG_H
