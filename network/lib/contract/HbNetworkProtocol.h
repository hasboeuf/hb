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

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbNetworkProtocol final {
    Q_GADGET

public:
    static QString msAppName;
    static quint16 msProtocolVersion;

    enum NetworkType : netwint {
        NETWORK_UNDEFINED = 0,
        NETWORK_TCP = 1 << 0,
        NETWORK_WEB = 1 << 1,
        NETWORK_SSL = 1 << 2,
        NETWORK_UDP = 1 << 3,
        NETWORK_LOCAL = 1 << 4,
        NETWORK_BLUETOOTH = 1 << 5
    };
    Q_ENUM(NetworkType)
    HB_ENUM(NetworkType)
    Q_DECLARE_FLAGS(NetworkTypes, NetworkType)

    enum RoutingScheme : netwint { ROUTING_UNDEFINED = 0, ROUTING_UNICAST, ROUTING_MULTICAST, ROUTING_BROADCAST };

    enum Service : serviceuid {
        SERVICE_UNDEFINED = 0,
        SERVICE_UPDATE = 1,
        SERVICE_KICK = 2,
        SERVICE_AUTH = 3,
        SERVICE_PRESENCE = 4,
        SERVICE_CHANNEL = 5,
        SERVICE_USER = 999
    };
    Q_ENUM(Service)
    HB_ENUM(Service)

    enum Code : codeuid {
        CODE_UNDEFINED = 0,
        CODE_CLT_AUTH_REQUEST,
        CODE_SRV_AUTH_STATUS,
        CODE_CLT_PRESENCE,
        CODE_SRV_PRESENCE_STATUS,
        CODE_SRV_KICK,
        CODE_SRV_USER_CONNECTED,

        CODE_USER = 999
    };
    Q_ENUM(Code)
    HB_ENUM(Code)

    enum KickCode : netwlint {
        KICK_UNDEFINED = 0,
        KICK_INTERNAL_ERROR,
        KICK_PROTOCOL_DIFFERENT,
        KICK_CONTRACT_INVALID,
        KICK_AUTH_LIMIT,
        KICK_AUTH_TIMEOUT,
        KICK_PRESENCE_TIMEOUT,

        KICK_USER = 999
    };
    Q_ENUM(KickCode)
    HB_ENUM(KickCode)

    enum AuthStatus : netwint {
        // General
        AUTH_INTERNAL_ERROR = 0,
        AUTH_BAD,
        AUTH_BAD_ID,
        AUTH_BAD_PASSWORD,
        AUTH_OK,
        AUTH_OK_ADMIN,
        // OAuth
        AUTH_OAUTH_KO
    };

    enum ServerStatus : netwint { SERVER_DISCONNECTED, SERVER_LISTENING };
    Q_ENUM(ServerStatus)
    HB_ENUM(ServerStatus)

    enum ClientStatus : netwint {
        CLIENT_DISCONNECTED,
        CLIENT_CONNECTING,
        CLIENT_CONNECTED,
        CLIENT_AUTHENTICATING,
        CLIENT_AUTHENTICATED
    };
    Q_ENUM(ClientStatus)
    HB_ENUM(ClientStatus)

    enum UserStatus : netwint {
        USER_DISCONNECTED,
        USER_CONNECTING,
        USER_CONNECTED,
        USER_AUTHENTICATING,
        USER_AUTHENTICATED,
    };
    Q_ENUM(UserStatus)
    HB_ENUM(UserStatus)

    enum NetworkUserStatus : netwint {
        NETWORK_USER_UNDEFINED,
        NETWORK_USER_CONNECTED,
        NETWORK_USER_LAGGED,
        NETWORK_USER_DISCONNECTED
    };
    Q_ENUM(NetworkUserStatus)
    HB_ENUM(NetworkUserStatus)
};
} // namespace network
} // namespace hb

Q_DECLARE_OPERATORS_FOR_FLAGS(hb::network::HbNetworkProtocol::NetworkTypes)

using hb::network::HbNetworkProtocol;

#endif // HBNETWORKPROTOCOL_H
