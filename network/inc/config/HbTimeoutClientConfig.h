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
            HbTimeoutClientConfig();
            virtual ~HbTimeoutClientConfig() = default;
            HbTimeoutClientConfig(const HbTimeoutClientConfig & config);
            virtual HbTimeoutClientConfig & operator =(const HbTimeoutClientConfig & config);

            virtual void setReconnectionDelay( quint16 duration ) final;
            virtual quint16 reconnectionDelay() const final;

            virtual bool isValid() const;

        private:
            quint16 mReconnectionDelay;

        };


    }
}

using hb::network::HbTimeoutClientConfig;

#endif // HBTIMEOUTCLIENTCONFIG_H
