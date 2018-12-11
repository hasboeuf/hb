/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBPRESENCECONTRACT_H
#define HBPRESENCECONTRACT_H

/*! \file HbPresenceContract.h */

// Qt
#include <QtCore/QObject>
#include <QtCore/QSet>
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
class HB_NETWORK_DECL HbPresenceContract : public HbNetworkContract {
public:
    HbPresenceContract();
    virtual ~HbPresenceContract() = default;
    HbPresenceContract(const HbPresenceContract& source);
    HbPresenceContract& operator=(const HbPresenceContract& source);

    virtual HbPresenceContract* create() const override;

    virtual bool read(QDataStream& stream) override;
    virtual bool write(QDataStream& stream) const override;

private:
};
} // namespace network
} // namespace hb

using hb::network::HbPresenceContract;

#endif // HBPRESENCECONTRACT_H
