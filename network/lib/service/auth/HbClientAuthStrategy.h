/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCLIENTAUTHSTRATEGY_H
#define HBCLIENTAUTHSTRATEGY_H

/*! \file HbClientAuthStrategy.h */

// Qt
// Hb
// Local
#include <service/auth/HbAuthStrategy.h>

namespace hb
{
    namespace network
    {
        class HbAuthRequestContract;
        class HbClientAuthLoginObject;

        /*!
         * TODOC
         */
        class HB_NETWORK_DECL HbClientAuthStrategy : public HbAuthStrategy
        {
            Q_OBJECT
        public:

            HbClientAuthStrategy() = default;
            virtual ~HbClientAuthStrategy() = default;

            virtual bool prepareAuthContract( HbClientAuthLoginObject * login_object ) = 0;

        signals:
            void authContractReady ( networkuid socket_uid, HbAuthRequestContract * contract );
            void authContractFailed( networkuid socket_uid, const QString & description );
        };
    }
}

using hb::network::HbClientAuthStrategy;

#endif // HBCLIENTAUTHSTRATEGY_H