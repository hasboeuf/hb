/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBGENERALSERVERCONFIG_H
#define HBGENERALSERVERCONFIG_H

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

        class HB_NETWORK_DECL HbGeneralServerConfig final : public HbGeneralConfig
        {

        public:
            HbGeneralServerConfig() = default;
            HbGeneralServerConfig( const HbGeneralServerConfig & config );
            virtual ~HbGeneralServerConfig() = default;
            virtual HbGeneralServerConfig & operator =( const HbGeneralServerConfig & config );

            virtual bool isValid() const;

        protected:

        };
    }
}

using hb::network::HbGeneralServerConfig;

#endif // HBGENERALSERVERCONFIG_H
