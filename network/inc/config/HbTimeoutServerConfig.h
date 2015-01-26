/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBTIMEOUTSERVERCONFIG_H
#define HBTIMEOUTSERVERCONFIG_H

// Qt
// Hb
// Local
#include <HbNetwork.h>
#include <config/HbTimeoutConfig.h>

namespace hb
{
    namespace network
    {
        class HB_NETWORK_DECL HbTimeoutServerConfig : public HbTimeoutConfig
        {

        public:

            virtual void setWarningThreshold( quint16 duration ) final;
            virtual quint16 warningThreshold() const final;

            virtual void setKickThreshold( quint16 duration ) final;
            virtual quint16 kickThreshold() const final;

            virtual bool isValid() const;

        protected:
            HbTimeoutServerConfig();
            HbTimeoutServerConfig(const HbTimeoutServerConfig & config);
            virtual ~HbTimeoutServerConfig() = default;
            virtual HbTimeoutServerConfig & operator =(const HbTimeoutServerConfig & config);

        private:
            quint16 mWarningThreshold;
            quint16 mKickThreshold;

        };


    }
}

using hb::network::HbTimeoutServerConfig;

#endif // HBTIMEOUTSERVERCONFIG_H
