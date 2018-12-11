/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBAUTHREQUESTCONTRACT_H
#define HBAUTHREQUESTCONTRACT_H

/*! \file HbAuthRequestContract.h */

// Qt
#include <QtCore/QObject>
#include <QtCore/QSet>
// Hb
#include <HbGlobal.h>
// Local
#include <HbNetwork.h>
#include <contract/HbNetworkContract.h>
#include <contract/auth/HbAuthStatusContract.h> // Covariance.

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbAuthRequestContract : public HbNetworkContract {
public:
    HbAuthRequestContract();
    virtual ~HbAuthRequestContract() = default;
    HbAuthRequestContract(const HbAuthRequestContract& source);
    HbAuthRequestContract& operator=(const HbAuthRequestContract& source);

    virtual HbAuthRequestContract* create() const override;

    HbAuthStatusContract* takeReply() const;

    virtual bool read(QDataStream& stream) override;
    virtual bool write(QDataStream& stream) const override;

    virtual authstgy type() const;
    virtual void setType(authstgy type);

protected:
    authstgy mType;
};
} // namespace network
} // namespace hb

using hb::network::HbAuthRequestContract;

#endif // HBAUTHREQUESTCONTRACT_H
