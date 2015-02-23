/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCLIENTAUTHLOGINOBJECT_H
#define HBCLIENTAUTHLOGINOBJECT_H

// Qt
// Hb
// Local
#include <service/auth/HbAuthService.h>

namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL HbClientAuthLoginObject
        {

        public:

            HbClientAuthLoginObject( authstgy strategy );
            HbClientAuthLoginObject() = delete;
            virtual ~HbClientAuthLoginObject() = default;

            virtual authstgy strategy() const final;

        protected:
            authstgy mStrategy;
        };
    }
}

using hb::network::HbClientAuthLoginObject;

#endif // HBCLIENTAUTHLOGINOBJECT_H
