/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef IHBSOCKETLISTENER_H
#define IHBSOCKETLISTENER_H

/*! \file IHbSocketListener.h */

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
        class HB_NETWORK_DECL IHbSocketListener
        {

        public callbacks:
            virtual void onSocketConnected   ( networkuid socket_uid ) = 0;
            virtual void onSocketDisconnected( networkuid socket_uid ) = 0;

        protected:
            virtual ~IHbSocketListener(){} //!< \todo defaulted linux-g++ issue
        };

    }
}

using hb::network::IHbSocketListener;

#endif // IHBSOCKETLISTENER_H