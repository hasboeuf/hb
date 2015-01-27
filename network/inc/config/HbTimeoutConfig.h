/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBTIMEOUTCONFIG_H
#define HBTIMEOUTCONFIG_H

// Qt
// Hb
// Local
#include <HbNetwork.h>

namespace hb
{
    namespace network
    {
        class HB_NETWORK_DECL HbTimeoutConfig
        {

        public:

            HbTimeoutConfig();
            virtual ~HbTimeoutConfig() = default;
            HbTimeoutConfig(const HbTimeoutConfig & config);
            virtual HbTimeoutConfig & operator =(const HbTimeoutConfig & config);

            virtual void setTickInterval( quint16 interval ) final;
            virtual quint16 tickInterval() const final;
            virtual bool isTimeoutEnabled() const final;

            virtual bool isValid() const;

        private:
            quint16 mTickInterval;

        };
    }
}

using hb::network::HbTimeoutConfig;

#endif // HBTIMEOUTCONFIG_H
