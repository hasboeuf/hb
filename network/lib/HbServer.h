/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVER_H
#define HBSERVER_H

/*! \file HbServer.h */

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <HbPeer.h>
#include <HbServerConnectionPool.h>
#include <config/peer/HbGeneralServerConfig.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbServer final : public HbPeer {
    Q_OBJECT
    Q_DISABLE_COPY(HbServer)
public:
    HbServer() = delete;
    HbServer(const HbGeneralServerConfig& config);
    virtual ~HbServer();

    networkuid joinTcpServer(HbTcpServerConfig& config, bool main);
    virtual bool leave() override;

signals:
    void serverStatusChanged(networkuid server_uid, HbNetworkProtocol::ServerStatus status);

private:
    HbServerConnectionPool mConnectionPool;
};
} // namespace network
} // namespace hb

#endif // HBSERVER_H
