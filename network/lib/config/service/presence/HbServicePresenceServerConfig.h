/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVICEPRESENCESERVERCONFIG_H
#define HBSERVICEPRESENCESERVERCONFIG_H

/*! \file HbServicePresenceServerConfig.h */

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <config/service/presence/HbServicePresenceConfig.h>

namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL HbServicePresenceServerConfig : public HbServicePresenceConfig
        {

        public:
            HbServicePresenceServerConfig();
            HbServicePresenceServerConfig( const HbServicePresenceServerConfig & config );
            virtual ~HbServicePresenceServerConfig() = default;
            virtual HbServicePresenceServerConfig & operator =( const HbServicePresenceServerConfig & config );

            virtual bool isValid() const;

            virtual void setWarningAliveThreshold( quint16 threshold ) final;
            virtual quint16 warningAliveThreshold() const final;

            virtual void setKickAliveThreshold( quint16 threshold ) final;
            virtual quint16 kickAliveThreshold() const final;

        protected:

        private:
            quint16 mWarningAliveThreshold;
            quint16 mKickAliveThreshold;

        };
    }
}

using hb::network::HbServicePresenceServerConfig;

#endif // HBSERVICEPRESENCESERVERCONFIG_H
