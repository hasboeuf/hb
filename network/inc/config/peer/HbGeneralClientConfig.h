/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBGENERALCLIENTCONFIG_H
#define HBGENERALCLIENTCONFIG_H

// Qt
#include <QtCore/QString>
#include <QtCore/QHash>
// Hb
// Local
#include <HbNetwork.h>
#include <config/peer/HbGeneralConfig.h>

namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL HbGeneralClientConfig final : public HbGeneralConfig
        {

        public:
            HbGeneralClientConfig();
            HbGeneralClientConfig( const HbGeneralClientConfig & config );
            virtual ~HbGeneralClientConfig() = default;
            virtual HbGeneralClientConfig & operator =( const HbGeneralClientConfig & config );

            virtual bool isValid() const;

        protected:

        };
    }
}

using hb::network::HbGeneralClientConfig;

#endif // HBGENERALCLIENTCONFIG_H
