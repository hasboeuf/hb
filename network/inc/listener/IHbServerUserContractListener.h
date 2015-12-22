/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef IHBSERVERUSERCONTRACTTLISTENER_H
#define IHBSERVERUSERCONTRACTTLISTENER_H

/*! \file IHbUserContractListener.h */

// Hb
#include <HbGlobal.h>
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkContract.h>
#include <user/HbNetworkUserInfo.h>

namespace hb
{
    namespace network
    {
        /*!
         * TODOC
         */
        class HB_NETWORK_DECL IHbServerUserContractListener
        {

        public callbacks:
            virtual void onUserContractReceived( ShConstHbNetworkUserInfo user_info, const HbNetworkContract * contract ) = 0;

        protected:
            virtual ~IHbServerUserContractListener(){} //!< \todo defaulted linux-g++ issue
        };

    }
}

using hb::network::IHbServerUserContractListener;

#endif // IHBSERVERUSERCONTRACTTLISTENER_H
