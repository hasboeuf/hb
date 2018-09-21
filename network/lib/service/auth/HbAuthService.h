/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBAUTHSERVICE_H
#define HBAUTHSERVICE_H

/*! \file HbAuthService.h */

// Qt
// Hb
// Local
#include <listener/IHbContractListener.h>
#include <listener/IHbSocketListener.h>
#include <service/HbNetworkService.h>
#include <user/HbNetworkUserInfo.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbAuthService : public HbNetworkService, public IHbContractListener, public IHbSocketListener {
    Q_OBJECT
public:
    enum AuthType : authstgy { AUTH_NONE = 0, AUTH_FACEBOOK, AUTH_GOOGLE, AUTH_USER = 255 };

    HbAuthService();
    virtual ~HbAuthService() {
    } //!< \todo defaulted linux-g++ issue

    virtual void plugContracts(HbNetworkExchanges& exchanges) override;

    virtual serviceuid uid() const override;

signals:
    void socketAuthenticated(networkuid socket_uid, const HbNetworkUserInfo& user_info);
    void socketUnauthenticated(networkuid socket_uid, quint8 try_number, quint8 max_tries, const QString& reason);

protected:
};
} // namespace network
} // namespace hb

#endif // HBAUTHSERVICE_H
