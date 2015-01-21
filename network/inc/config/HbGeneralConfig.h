/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBGENERALCONFIG_H
#define HBGENERALCONFIG_H

// Qt
#include <QtCore/QString>
#include <QtCore/QHash>
// Hb
// Local
#include <HbNetwork.h>

namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL HbGeneralConfig final
        {

        public:
            HbGeneralConfig();
            HbGeneralConfig( const HbGeneralConfig & config );
            virtual ~HbGeneralConfig() = default;

            virtual HbGeneralConfig & operator =( const HbGeneralConfig & config );

            virtual bool isValid() const;

            const QString & appName() const;
            quint16 protocolVersion() const;

            void setAppName( const QString & app_name );
            void setProtocolVersion( quint16 protocol_version );

        protected:

        private:
            QString mAppName;
            quint16 mProtocolVersion;
        };
    }
}

using hb::network::HbGeneralConfig;

#endif // HBGENERALCONFIG_H
