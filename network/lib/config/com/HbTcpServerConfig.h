/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBTCPSERVERCONFIG_H
#define HBTCPSERVERCONFIG_H

/*! \file HbTcpServerConfig.h */

// Qt
#include <QtNetwork/QHostAddress>
// Local
#include <config/com/HbServerConfig.h>
#include <config/com/HbTcpConfig.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbTcpServerConfig final : public virtual HbNetworkConfig,
                                                public HbTcpConfig,
                                                public HbServerConfig {
public:
    HbTcpServerConfig() = default;
    virtual ~HbTcpServerConfig() = default;
    HbTcpServerConfig(const HbTcpServerConfig& config);
    HbTcpServerConfig& operator=(const HbTcpServerConfig& config);

    bool isValid() const;
};
} // namespace network
} // namespace hb

using hb::network::HbTcpServerConfig;

#endif // HBTCPSERVERCONFIG_H
