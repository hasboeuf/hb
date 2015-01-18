#ifndef HBTCPSERVERCONFIG_H
#define HBTCPSERVERCONFIG_H

// Qt
#include <QtNetwork/QHostAddress>
// Local
#include <config/HbServerConfig.h>
#include <config/HbTcpConfig.h>


namespace hb
{
	namespace network
	{

		class HB_NETWORK_DECL HbTcpServerConfig final :
			public virtual HbNetworkConfig,
			public HbTcpConfig,
			public HbServerConfig
		{
		public:

			HbTcpServerConfig( );
			HbTcpServerConfig( const HbTcpServerConfig & config );
			virtual ~HbTcpServerConfig( ) = default;

			HbTcpServerConfig & operator =( const HbTcpServerConfig & config );

			bool isValid() const;

		};
	}
}

using hb::network::HbTcpServerConfig;

#endif // HBTCPSERVERCONFIG_H
