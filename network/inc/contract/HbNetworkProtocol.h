/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNETWORKPROTOCOL_H
#define HBNETWORKPROTOCOL_H

namespace hb
{
	namespace network
	{
        class HbNetworkProtocol final
		{

        public:

            enum RoutingScheme : quint8
            {
                UNICAST = 0,
                MULTICAST = 1,
                BROADCAST = 2
            };

            enum Service : quint16
            {
                SERVICE_UNDEFINED = 0,
                SERVICE_UPDATE = 1,
                SERVICE_AUTH = 2,
                SERVICE_TIMEOUT = 3,

                SERVICE_USER = 255
            };

            enum Code : quint16
            {
                CODE_UNDEFINED = 0,
                CODE_CONNECTION_REQUEST = 1
            };

        };
	}
}

#endif // HBNETWORKPROTOCOL_H
