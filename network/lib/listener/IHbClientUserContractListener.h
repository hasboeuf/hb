/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef IHBCLIENTUSERCONTRACTTLISTENER_H
#define IHBCLIENTUSERCONTRACTTLISTENER_H

/*! \file IHbUserContractListener.h */

// Hb
#include <HbGlobal.h>
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkContract.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL IHbClientUserContractListener {
public:
    virtual void onUserContractReceived(const HbNetworkContract* contract) = 0;

protected:
    virtual ~IHbClientUserContractListener() {
    } //!< \todo defaulted linux-g++ issue
};

} // namespace network
} // namespace hb

using hb::network::IHbClientUserContractListener;

#endif // IHBCLIENTUSERCONTRACTTLISTENER_H
