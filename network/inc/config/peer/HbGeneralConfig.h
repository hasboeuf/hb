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
#include <service/auth/HbServerAuthStrategy.h>
#include <service/channel/HbNetworkChannel.h>

namespace hb
{
    namespace network
    {

        class HB_NETWORK_DECL HbGeneralConfig
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

            template< class A >
            A * enableAuthentication()
            {
                A * strategy = new A();
                if( dynamic_cast< HbServerAuthStrategy * >( strategy ) )
                {
                    mpAuthenticationStrategy = strategy;
                    return strategy;
                }
                return nullptr;
            }

            template< class C >
            C * registerChannel()
            {
                C * channel = new C();
                if( dynamic_cast< HbNetworkChannel * >( channel ) )
                {
                    mChannels.append( channel );
                    return channel;
                }
                return nullptr;
            }

        protected:

        private:
            QString mAppName;
            quint16 mProtocolVersion;
            HbServerAuthStrategy * mpAuthenticationStrategy;
            QList< HbNetworkChannel * > mChannels;
        };
    }
}

using hb::network::HbGeneralConfig;

#endif // HBGENERALCONFIG_H
