/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNETWORKPROTOCOL_H
#define HBNETWORKPROTOCOL_H

/*! \file HbNetworkProtocol.h */

// Qt
#include <QtCore/QString>
// Hb
#include <HbGlobal.h>
#include <core/HbEnum.h>
// Local
#include <HbNetwork.h>

namespace hb
{
    namespace network
    {
        /*!
         * TODOC
         */
        class HB_NETWORK_DECL HbNetworkProtocol final
        {
            Q_GADGET
            Q_ENUMS_HANDLER( HbNetworkProtocol )
            Q_ENUMS( NetworkType )
            Q_ENUMS( Service )
            Q_ENUMS( Code )
            Q_ENUMS( ServerStatus )
            Q_ENUMS( ClientStatus )
            Q_ENUMS( UserStatus )
            Q_ENUMS( KickCode )

        public:
            static QString msAppName;
            static quint16 msProtocolVersion;

            enum NetworkType : netwint
            {
                NETWORK_UNDEFINED = 0,
                NETWORK_TCP       = 1 << 0,
                NETWORK_WEB       = 1 << 1,
                NETWORK_SSL       = 1 << 2,
                NETWORK_UDP       = 1 << 3,
                NETWORK_LOCAL     = 1 << 4,
                NETWORK_BLUETOOTH = 1 << 5
            };
            Q_META_ENUMS( NetworkType )
            Q_DECLARE_FLAGS( NetworkTypes, NetworkType )

            enum RoutingScheme : netwint
            {
                ROUTING_UNDEFINED = 0,
                ROUTING_UNICAST,
                ROUTING_MULTICAST,
                ROUTING_BROADCAST
            };

            enum Service : serviceuid
            {
                SERVICE_UNDEFINED = 0,
                SERVICE_UPDATE    = 1,
                SERVICE_KICK      = 2,
                SERVICE_AUTH      = 3,
                SERVICE_PRESENCE  = 4,
                SERVICE_CHANNEL   = 255,

                SERVICE_USER      = SERVICE_CHANNEL
            };
            Q_META_ENUMS( Service )

            enum Code : codeuid
            {
                CODE_UNDEFINED            = 0,
                CODE_CLT_AUTH_REQUEST,
                CODE_SRV_AUTH_STATUS,
                CODE_CLT_PRESENCE,
                CODE_SRV_PRESENCE_STATUS,
                CODE_SRV_KICK,

                CODE_USER                 = 1989


            };
            Q_META_ENUMS( Code )

            enum KickCode : netwint
            {
                KICK_UNDEFINED = 0,
                KICK_INTERNAL_ERROR,
                KICK_PROTOCOL_DIFFERENT,
                KICK_CONTRACT_INVALID,
                KICK_AUTH_LIMIT,
                KICK_AUTH_TIMEOUT,
                KICK_PRESENCE_TIMEOUT

            };
            Q_META_ENUMS( KickCode )

            enum AuthStatus : netwint
            {
                // General
                AUTH_INTERNAL_ERROR = 0,
                AUTH_BAD,
                AUTH_BAD_ID,
                AUTH_BAD_PASSWORD,
                AUTH_OK,
                AUTH_OK_ADMIN,
                // Facebook
                AUTH_FB_KO
            };

            enum ServerStatus : netwint
            {
                SERVER_DISCONNECTED,
                SERVER_LISTENING
            };
            Q_META_ENUMS( ServerStatus )

            enum ClientStatus : netwint
            {
                CLIENT_DISCONNECTED,
                CLIENT_CONNECTING,
                CLIENT_CONNECTED,
                CLIENT_AUTHENTICATING,
                CLIENT_AUTHENTICATED
            };
            Q_META_ENUMS( ClientStatus )

            enum UserStatus : netwint
            {
                USER_DISCONNECTED,
                USER_CONNECTING,
                USER_CONNECTED,
                USER_AUTHENTICATING,
                USER_AUTHENTICATED,

            };
            Q_META_ENUMS( UserStatus )

        };
    }
}

Q_DECLARE_OPERATORS_FOR_FLAGS( hb::network::HbNetworkProtocol::NetworkTypes )

using hb::network::HbNetworkProtocol;

#endif // HBNETWORKPROTOCOL_H
