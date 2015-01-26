/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNETWORKPROTOCOL_H
#define HBNETWORKPROTOCOL_H

// Qt
#include <QtCore/QString>
// Local
#include <HbNetwork.h>

namespace hb
{
	namespace network
	{
        // TODO decl temp
        class HB_NETWORK_DECL HbNetworkProtocol final
		{

        public:
            static QString msAppName;
            static quint16 msProtocolVersion;

            enum NetworkType : qint16
            {
                NETWORK_UNDEFINED = 0,
                NETWORK_TCP,
                NETWORK_WEB,
                NETWORK_SSL,
                NETWORK_UDP,
                NETWORK_LOCAL,
                NETWORK_BLUETOOTH
            };

            enum RoutingScheme : quint8
            {
                UNICAST = 0,
                MULTICAST = 1,
                BROADCAST = 2
            };

            enum Service : servuuid
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

            enum AuthenticationStatus : quint8
            {
                AUTH_INTERNAL_ERROR = 0,
                AUTH_BAD_UUID,
                AUTH_BAD_PASSWORD,
                AUTH_OK,
                AUTH_OK_ADMIN
            };

        };
	}
}

using hb::network::HbNetworkProtocol;

#endif // HBNETWORKPROTOCOL_H
