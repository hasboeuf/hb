/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVERCONFIG_H
#define HBSERVERCONFIG_H

/*! \file HbServerConfig.h */

// Qt
#include <QtCore/QtGlobal>
// Local
#include <HbNetwork.h>
#include <config/com/HbNetworkConfig.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbServerConfig : public virtual HbNetworkConfig {
public:
    HbServerConfig();
    virtual ~HbServerConfig() = default;
    HbServerConfig(const HbServerConfig& config);
    HbServerConfig& operator=(const HbServerConfig& config);

    bool isValid() const;

    virtual void setMaxUsersPerThread(quint16 max_users) final;
    virtual quint16 maxUsersPerThread() const final;
    virtual bool isThreaded() const final;

private:
    quint16 mMaxUsersPerThread;
};
} // namespace network
} // namespace hb

using hb::network::HbServerConfig;

#endif // HBSERVERCONFIG_H
