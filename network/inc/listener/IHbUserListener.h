/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef IHBUSERTLISTENER_H
#define IHBUSERTLISTENER_H

// Hb
#include <HbGlobal.h>
// Local
#include <HbNetwork.h>
#include <user/HbNetworkUserInfo.h>

namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL IHbUserListener
        {

        public callbacks:
            virtual void onUserConnected   ( const HbNetworkUserInfo & user_info ) = 0;
            virtual void onUserDisconnected( const HbNetworkUserInfo & user_info ) = 0;

        protected:
            virtual ~IHbUserListener() = default;
        };

    }
}

Q_DECLARE_INTERFACE( hb::network::IHbUserListener, "hb::network::IHbUserListener" )

using hb::network::IHbUserListener;

#endif // IHBUSERTLISTENER_H
