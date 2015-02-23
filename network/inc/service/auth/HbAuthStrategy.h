/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBAUTHSTRATEGY_H
#define HBAUTHSTRATEGY_H

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkProtocol.h>
#include <user/HbNetworkUserInfo.h>

namespace hb
{
    namespace network
    {
        class HB_NETWORK_DECL HbAuthStrategy : public QObject
        {
            Q_OBJECT
        public:

            HbAuthStrategy() = default;
            virtual ~HbAuthStrategy() = default;

            virtual authstgy type() const = 0;

        signals:
            void loginSucceed( networkuid sender,
                               const HbNetworkUserInfo & user );
            void loginFailed(  networkuid sender,
                               const HbNetworkProtocol::AuthStatus & status,
                               const QString & description );
        };
    }
}

using hb::network::HbAuthStrategy;

#endif // HBAUTHSTRATEGY_H
