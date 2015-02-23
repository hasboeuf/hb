/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCLIENTAUTHSTRATEGY_H
#define HBCLIENTAUTHSTRATEGY_H

// Qt
// Hb
// Local
#include <service/auth/HbAuthStrategy.h>

namespace hb
{
    namespace network
    {
        class HbClientAuthLoginObject;

        class HB_NETWORK_DECL HbClientAuthStrategy : public HbAuthStrategy
        {
            Q_OBJECT
        public:

            HbClientAuthStrategy() = default;
            virtual ~HbClientAuthStrategy() = default;

            virtual authstgy type() const = 0;

            virtual bool tryLogin( HbClientAuthLoginObject * login_object ) = 0;

        };
    }
}

using hb::network::HbClientAuthStrategy;

#endif // HBCLIENTAUTHSTRATEGY_H
