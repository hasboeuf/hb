/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVICEAUTHCONFIG_H
#define HBSERVICEAUTHCONFIG_H

/*! \file HbServiceAuthConfig.h */

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <config/service/HbServiceConfig.h>

namespace hb {
namespace network {

class HB_NETWORK_DECL HbServiceAuthConfig : public HbServiceConfig {
public:
    HbServiceAuthConfig();
    HbServiceAuthConfig(const HbServiceAuthConfig& config);
    virtual ~HbServiceAuthConfig() {
    } //!< \todo defaulted linux-g++ issue
    virtual HbServiceAuthConfig& operator=(const HbServiceAuthConfig& config);

    virtual bool isValid() const;

protected:
private:
};
} // namespace network
} // namespace hb

using hb::network::HbServiceAuthConfig;

#endif // HBSERVICEAUTHCONFIG_H
