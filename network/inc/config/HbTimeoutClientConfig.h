/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBTIMEOUTCLIENTCONFIG_H
#define HBTIMEOUTCLIENTCONFIG_H

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <config/HbTimeoutConfig.h>

namespace hb
{
    namespace network
    {
        class HB_NETWORK_DECL HbTimeoutClientConfig : public HbTimeoutConfig
        {

        public:

            virtual void setReconnectionDelay( quint16 duration ) final;
            virtual quint16 reconnectionDelay() const final;

            virtual bool isValid() const;

        protected:
            HbTimeoutClientConfig();
            HbTimeoutClientConfig(const HbTimeoutClientConfig & config);
            virtual ~HbTimeoutClientConfig() = default;
            virtual HbTimeoutClientConfig & operator =(const HbTimeoutClientConfig & config);

        private:
            quint16 mReconnectionDelay;

        };


    }
}

using hb::network::HbTimeoutServerConfig;

#endif // HBTIMEOUTCLIENTCONFIG_H
