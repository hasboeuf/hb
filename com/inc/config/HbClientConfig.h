/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCLIENTCONFIG_H
#define HBCLIENTCONFIG_H

// Qt
#include <QtCore/QtGlobal>
// Local
#include <HbCom.h>
#include <config/HbComConfig.h>

namespace hb
{
    namespace com
    {

        class HB_COM_DECL HbClientConfig : public virtual HbComConfig
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

using hb::com::HbClientConfig;

#endif // HBCLIENTCONFIG_H
