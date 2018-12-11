/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNETWORKCHANNEL_H
#define HBNETWORKCHANNEL_H

/*! \file HbNetworkChannel.h */

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <service/HbNetworkService.h>

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbNetworkChannel : public HbNetworkService {
public:
    HbNetworkChannel();
    virtual ~HbNetworkChannel() = default;

    virtual void internalReset(bool keep_uid = false); //!< \todo Make it protected.

    void setNetworkUid(networkuid network_uid);
    networkuid networkUid() const;

    // Hide service side signals.
    void socketToKick(networkuid socket_uid, netwlint reason, const QString& description = QString()) = delete;

    virtual void onContractToSend(HbNetworkContract* contract) = 0;

protected:
    networkuid mNetworkUid;
};
} // namespace network
} // namespace hb

#endif // HBNETWORKCHANNEL_H
