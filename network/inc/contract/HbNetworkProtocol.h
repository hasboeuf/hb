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
                NETWORK_TCP       = 1 << 0,
                NETWORK_WEB       = 1 << 1,
                NETWORK_SSL       = 1 << 2,
                NETWORK_UDP       = 1 << 3,
                NETWORK_LOCAL     = 1 << 4,
                NETWORK_BLUETOOTH = 1 << 5
            };
            Q_DECLARE_FLAGS( NetworkTypes, NetworkType )

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
                SERVICE_PRESENCE = 3,

                SERVICE_UNDEFINED_USER = 255
            };

            enum Code : quint16
            {
                CODE_UNDEFINED = 0,
                CODE_AUTH_REQUEST,
                CODE_AUTH_STATUS,
                CODE_PRESENCE,
                CODE_PRESENCE_STATUS
            };

            enum AuthStatus : quint8
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

Q_DECLARE_OPERATORS_FOR_FLAGS( hb::network::HbNetworkProtocol::NetworkTypes )

using hb::network::HbNetworkProtocol;

#endif // HBNETWORKPROTOCOL_H
