#ifndef HBSERVERCONFIG_H
#define HBSERVERCONFIG_H

// Qt
#include <QtCore/QtGlobal>
// Local
#include <HbNetwork.h>
#include <HbNetworkConfig.h>

namespace hb
{
	namespace network
	{

		class HB_NETWORK_DECL HbServerConfig : public virtual HbNetworkConfig
		{

		public:

			HbServerConfig();
			HbServerConfig( const HbServerConfig & config );
			virtual ~HbServerConfig() = default;

			HbServerConfig & operator =( const HbServerConfig & config );

			virtual void setMaxUsersPerThread( quint16 max_users ) final;
			virtual quint16 maxUsersPerThread() const final;
			virtual bool isThreaded() const final;

			bool isValid() const;

		private:
			quint16 mMaxUsersPerThread;
		};

	}
}

using hb::network::HbServerConfig;

#endif // HBSERVERCONFIG_H
