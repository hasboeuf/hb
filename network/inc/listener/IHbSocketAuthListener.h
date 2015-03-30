/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef IHBSOCKETAUTHLISTENER_H
#define IHBSOCKETAUTHLISTENER_H

/*! \file IHbSocketAuthListener.h */

// Hb
#include <HbGlobal.h>
// Local
#include <HbNetwork.h>

namespace hb
{
    namespace network
    {
        /*!
         * TODOC
         */
        class HB_NETWORK_DECL IHbSocketAuthListener
        {

        public callbacks:
            virtual void onSocketAuthenticated  ( networkuid socket_uid ) = 0;
            virtual void onSocketUnauthenticated( networkuid socket_uid ) = 0;

        protected:
            virtual ~IHbSocketAuthListener(){} //!< \todo defaulted linux-g++ issue
        };

    }
}

using hb::network::IHbSocketAuthListener;

#endif // IHBSOCKETAUTHLISTENER_H
