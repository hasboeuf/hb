/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBGENERALSERVERCONFIG_H
#define HBGENERALSERVERCONFIG_H

/*! \file HbGeneralServerConfig.h */

// Qt
#include <QtCore/QString>
#include <QtCore/QHash>
// Hb
// Local
#include <HbNetwork.h>
#include <config/peer/HbGeneralConfig.h>
#include <config/service/auth/HbServiceAuthServerConfig.h>
#include <config/service/channel/HbServiceChannelServerConfig.h>
#include <config/service/presence/HbServicePresenceServerConfig.h>

namespace hb
{
    namespace network
    {
        /*!
         * TODOC
         */
        class HB_NETWORK_DECL HbGeneralServerConfig final : public HbGeneralConfig
        {

        public:
            HbGeneralServerConfig() = default;
            HbGeneralServerConfig( const HbGeneralServerConfig & config );
            virtual ~HbGeneralServerConfig() = default;
            virtual HbGeneralServerConfig & operator =( const HbGeneralServerConfig & config );

            virtual bool isValid() const;

            HbServiceAuthServerConfig     & auth    ();
            HbServiceChannelServerConfig  & channel ();
            HbServicePresenceServerConfig & presence();

            const HbServiceAuthServerConfig     & auth    () const;
            const HbServiceChannelServerConfig  & channel () const;
            const HbServicePresenceServerConfig & presence() const;

        protected:

        private:
            HbServiceAuthServerConfig     mAuthConfig;
            HbServiceChannelServerConfig  mChannelConfig;
            HbServicePresenceServerConfig mPresenceConfig;
        };
    }
}

using hb::network::HbGeneralServerConfig;

#endif // HBGENERALSERVERCONFIG_H
