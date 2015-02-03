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
#include <config/com/HbNetworkConfig.h>
#include <config/com/HbTimeoutServerConfig.h>

namespace hb
{
	namespace network
	{

		class HB_NETWORK_DECL HbServerConfig : public virtual HbNetworkConfig
		{

		public:

			HbServerConfig();
            virtual ~HbServerConfig() = default;
			HbServerConfig( const HbServerConfig & config );
			HbServerConfig & operator =( const HbServerConfig & config );

			virtual void setMaxUsersPerThread( quint16 max_users ) final;
			virtual quint16 maxUsersPerThread() const final;
			virtual bool isThreaded() const final;

            const HbTimeoutServerConfig & timeout() const;
            void setTimeout( const HbTimeoutServerConfig & timeout );

            virtual void setAuthTriesMax( quint16 max ) final;
            virtual quint16 authTriesMax() const;

			bool isValid() const;

		private:
			quint16 mMaxUsersPerThread;
            HbTimeoutServerConfig mTimeout;
            quint16 mAuthTriesMax;
		};
	}
}

using hb::network::HbServerConfig;

#endif // HBSERVERCONFIG_H