/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVERAUTHSTRATEGY_H
#define HBSERVERAUTHSTRATEGY_H

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkProtocol.h>
#include <contract/auth/HbAuthRequestContract.h> // Template.
#include <user/HbNetworkUserInfo.h>

namespace hb
{
	namespace network
	{
        class HbAuthRequestContract;

        class HB_NETWORK_DECL HbServerAuthStrategy : public QObject
		{
            Q_OBJECT
		public:

            HbServerAuthStrategy() = default;
            virtual ~HbServerAuthStrategy() = default;

            virtual bool tryLogin( const HbAuthRequestContract * contract ) = 0;
            virtual authstgy type() const = 0;

        signals:
            void loginSucceed( sockuuid sender,
                               const HbNetworkUserInfo & user );
            void loginFailed(  sockuuid sender,
                               const HbNetworkProtocol::AuthStatus & status,
                               const QString & description );
		};
	}
}

using hb::network::HbServerAuthStrategy;

#endif // HBSERVERAUTHSTRATEGY_H
