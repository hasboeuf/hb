/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCLIENTPRESENCESERVICE_H
#define HBCLIENTPRESENCESERVICE_H

/*! \file HbClientPresenceService.h */

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <config/service/presence/HbServicePresenceClientConfig.h>
#include <service/presence/HbPresenceService.h>

class QTimerEvent;

namespace hb {
namespace network {
/*!
 * TODOC
 */
class HB_NETWORK_DECL HbClientPresenceService : public HbPresenceService {
    Q_OBJECT

public:
    HbClientPresenceService();
    virtual ~HbClientPresenceService() = default;

    virtual void reset() override;

    const HbServicePresenceClientConfig& config() const;
    void setConfig(const HbServicePresenceClientConfig& config);

protected:
    void timerEvent(QTimerEvent*);

public
    callbacks : void onSocketAuthenticated(networkuid socket_uid) override;
    void onSocketUnauthenticated(networkuid socket_uid) override;

private:
    HbServicePresenceClientConfig mConfig;
    QHash<networkuid, qint32> mTimerBySocketUid;
    QHash<qint32, networkuid> mSocketByTimerId;
};
} // namespace network
} // namespace hb

#endif // HBCLIENTPRESENCESERVICE_H
