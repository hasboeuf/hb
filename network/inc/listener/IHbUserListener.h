/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef IHBUSERTLISTENER_H
#define IHBUSERTLISTENER_H

/*! \file IHbUserListener.h */

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
        class HB_NETWORK_DECL IHbUserListener
        {

        public callbacks:
            virtual void onUserConnected   ( const HbNetworkUserData & user_data ) = 0;
            virtual void onUserDisconnected( const HbNetworkUserData & user_data ) = 0;

        protected:
            virtual ~IHbUserListener(){} //!< \todo defaulted linux-g++ issue
        };

    }
}

using hb::network::IHbUserListener;

#endif // IHBUSERTLISTENER_H
