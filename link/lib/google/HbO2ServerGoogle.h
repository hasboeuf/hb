/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBO2SERVERGOOGLE_H
#define HBO2SERVERGOOGLE_H

// Qt
// Local
#include <HbLink.h>
#include <HbO2Server.h>

namespace hb {
namespace link {
/*!
 * HbO2ServerGoogle is the Google implementation of HbO2Server.
 */
class HB_LINK_DECL HbO2ServerGoogle : public HbO2Server {
    Q_OBJECT

public:
    HbO2ServerGoogle() = default;
    virtual ~HbO2ServerGoogle() = default;

protected:
    virtual const QUrl endPoint() const override;
    virtual const QHash<QString, QString> tokenRequest() const override;
    virtual LinkStatus tokenResponse(const QByteArray& data) override;
};
} // namespace link
} // namespace hb

using hb::link::HbO2ServerGoogle;

#endif // HBO2SERVERGOOGLE_H
