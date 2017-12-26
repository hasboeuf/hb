/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCLIENTAUTHLOGINOBJECT_H
#define HBCLIENTAUTHLOGINOBJECT_H

/*! \file HbClientAuthLoginObject.h */

// Qt
// Hb
// Local
#include <service/auth/HbAuthService.h>

namespace hb
{
    namespace network
    {
        /*!
         * TODOC
         */
        class HB_NETWORK_DECL HbClientAuthLoginObject
        {

        public:

            HbClientAuthLoginObject();
            virtual ~HbClientAuthLoginObject() = default;

            virtual void setStrategy ( authstgy strategy ) final;
            virtual void setSocketUid( networkuid socket_uid ) final;

            virtual authstgy   strategy() const final;
            virtual networkuid socketUid() const final;

        protected:
            authstgy mStrategy;
            networkuid mSocketUid;
        };
    }
}

using hb::network::HbClientAuthLoginObject;

#endif // HBCLIENTAUTHLOGINOBJECT_H
