/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef IHBSOCKETTLISTENER_H
#define IHBSOCKETTLISTENER_H

#include <QtCore/QtPlugin>
// Hb
#include <HbGlobal.h>
// Local
#include <HbNetwork.h>

namespace hb
{
	namespace network
	{

        class HB_NETWORK_DECL IHbSocketListener
		{

        public callbacks:
            virtual void onSocketConnected   ( sockuuid socket_uuid ) = 0;
            virtual void onSocketDisconnected( sockuuid socket_uuid ) = 0;

        protected:
            virtual ~IHbSocketListener() = default;
		};

	}
}

Q_DECLARE_INTERFACE( hb::network::IHbSocketListener, "hb::network::IHbSocketListener" )

using hb::network::IHbSocketListener;

#endif // IHBSOCKETTLISTENER_H
