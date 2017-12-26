/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVERPRESENCESERVICE_H
#define HBSERVERPRESENCESERVICE_H

/*! \file HbServerPresenceService.h */

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <service/presence/HbPresenceService.h>
#include <listener/IHbContractListener.h>
#include <config/service/presence/HbServicePresenceServerConfig.h>

class QTimerEvent;

namespace hb
{
    namespace network
    {
        /*!
         * TODOC
         */
        class HB_NETWORK_DECL HbServerPresenceService :
            public HbPresenceService,
            public IHbContractListener
        {
            Q_OBJECT

        public:

            HbServerPresenceService();
            virtual ~HbServerPresenceService() = default;

            virtual void reset() override;

            const HbServicePresenceServerConfig & config() const;
            void setConfig( const HbServicePresenceServerConfig & config );

        protected:
            void timerEvent( QTimerEvent * );

        public callbacks:
            virtual void onSocketAuthenticated  ( networkuid socket_uid ) override;
            virtual void onSocketUnauthenticated( networkuid socket_uid ) override;
            virtual void onContractReceived( const HbNetworkContract * contract ) override;

        signals:
            void socketLagged( networkuid socket_uid, quint16 last_presence, quint16 kick_threshold );

        private:
            HbServicePresenceServerConfig mConfig;
            qint32 mTickTimer;
            QHash< networkuid, quint16 > mClientAliveTick;
        };
    }
}

#endif // HBSERVERPRESENCESERVICE_H
