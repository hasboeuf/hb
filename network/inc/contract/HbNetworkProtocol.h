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
// Hb
#include <HbGlobal.h>
#include <core/HbEnum.h>
// Local
#include <HbNetwork.h>

namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL HbNetworkProtocol final
        {
            Q_GADGET
            Q_ENUMS_HANDLER( HbNetworkProtocol )
            Q_ENUMS( Service )
            Q_ENUMS( Code )

        public:
            static QString msAppName;
            static quint16 msProtocolVersion;

            enum NetworkType : quint8
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

            enum Service : servuid
            {
                SERVICE_UNDEFINED = 0,
                SERVICE_UPDATE = 1,
                SERVICE_AUTH = 2,
                SERVICE_PRESENCE = 3,

                SERVICE_CHANNEL = 255,
                SERVICE_CHANNEL_USER
            };
            Q_META_ENUMS( Service )

            enum Code : netwcode
            {
                CODE_UNDEFINED = 0,
                CODE_CLT_AUTH_REQUEST,
                CODE_SRV_AUTH_STATUS,
                CODE_CLT_PRESENCE,
                CODE_SRV_PRESENCE_STATUS
            };
            Q_META_ENUMS( Code )

            enum KickCode : kickcode
            {
                KICK_INTERNAL_ERROR = 0,
                KICK_PROTOCOL_DIFFERENT,
                KICK_CONTRACT_INVALID,
                KICK_AUTH_LIMIT,
                KICK_PRESENCE_TIMEOUT

            };
            Q_META_ENUMS( KickCode )

            enum AuthStatus : netwcode
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

        };
    }
}

Q_DECLARE_OPERATORS_FOR_FLAGS( hb::network::HbNetworkProtocol::NetworkTypes )

using hb::network::HbNetworkProtocol;

#endif // HBNETWORKPROTOCOL_H
