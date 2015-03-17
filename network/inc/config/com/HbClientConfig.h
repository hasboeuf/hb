/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCLIENTCONFIG_H
#define HBCLIENTCONFIG_H

/*! \file HbClientConfig.h */

// Qt
#include <QtCore/QtGlobal>
// Local
#include <HbNetwork.h>
#include <config/com/HbNetworkConfig.h>

namespace hb
{
    namespace network
    {
        /*!
         * TODOC
         */
        class HB_NETWORK_DECL HbClientConfig : public virtual HbNetworkConfig
        {

        public:
            HbClientConfig();
            virtual ~HbClientConfig() = default;
            HbClientConfig( const HbClientConfig & config );
            HbClientConfig & operator =( const HbClientConfig & config );

            bool isValid() const;

            virtual void setReconnectionDelay( quint16 duration ) final;
            virtual quint16 reconnectionDelay() const final;

        private:
            quint16 mReconnectionDelay;
        };
    }
}

using hb::network::HbClientConfig;

#endif // HBCLIENTCONFIG_H
