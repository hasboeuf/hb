/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBGENERALCLIENTCONFIG_H
#define HBGENERALCLIENTCONFIG_H

/*! \file HbGeneralClientConfig.h */

// Qt
#include <QtCore/QString>
#include <QtCore/QHash>
// Hb
// Local
#include <HbNetwork.h>
#include <config/peer/HbGeneralConfig.h>
#include <config/service/auth/HbServiceAuthClientConfig.h>
#include <config/service/channel/HbServiceChannelClientConfig.h>
#include <config/service/presence/HbServicePresenceClientConfig.h>

namespace hb
{
    namespace network
    {
        /*!
         * TODOC
         */
        class HB_NETWORK_DECL HbGeneralClientConfig final : public HbGeneralConfig
        {

        public:
            HbGeneralClientConfig() = default;
            HbGeneralClientConfig( const HbGeneralClientConfig & config );
            virtual ~HbGeneralClientConfig() = default;
            virtual HbGeneralClientConfig & operator =( const HbGeneralClientConfig & config );

            virtual bool isValid() const;

            HbServiceAuthClientConfig     & auth    ();
            HbServiceChannelClientConfig  & channel ();
            HbServicePresenceClientConfig & presence();

            const HbServiceAuthClientConfig     & auth    () const;
            const HbServiceChannelClientConfig  & channel () const;
            const HbServicePresenceClientConfig & presence() const;

        protected:

        private:
            HbServiceAuthClientConfig     mAuthConfig;
            HbServiceChannelClientConfig  mChannelConfig;
            HbServicePresenceClientConfig mPresenceConfig;
        };
    }
}

using hb::network::HbGeneralClientConfig;

#endif // HBGENERALCLIENTCONFIG_H
