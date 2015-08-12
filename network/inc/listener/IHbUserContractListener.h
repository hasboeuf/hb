/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef IHBUSERCONTRACTTLISTENER_H
#define IHBUSERCONTRACTTLISTENER_H

/*! \file IHbUserContractListener.h */

// Hb
#include <HbGlobal.h>
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkContract.h>
#include <user/HbNetworkUserData.h>

namespace hb
{
    namespace network
    {
        /*!
         * TODOC
         */
        class HB_NETWORK_DECL IHbUserContractListener
        {

        public callbacks:
            virtual void onUserContractReceived( const HbNetworkUserData & user_data, const HbNetworkContract * contract ) = 0;

        protected:
            virtual ~IHbUserContractListener(){} //!< \todo defaulted linux-g++ issue
        };

    }
}

using hb::network::IHbUserContractListener;

#endif // IHBUSERCONTRACTTLISTENER_H
