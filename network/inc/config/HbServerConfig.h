/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVERCONFIG_H
#define HBSERVERCONFIG_H

// Qt
#include <QtCore/QtGlobal>
// Local
#include <HbNetwork.h>
#include <config/HbNetworkConfig.h>

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
