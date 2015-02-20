/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBSERVERCONFIG_H
#define HBSERVERCONFIG_H

// Qt
#include <QtCore/QtGlobal>
// Local
#include <HbCom.h>
#include <config/HbComConfig.h>

namespace hb
{
    namespace com
    {

        class HB_COM_DECL HbServerConfig : public virtual HbComConfig
        {

        public:

            HbServerConfig();
            virtual ~HbServerConfig() = default;
            HbServerConfig( const HbServerConfig & config );
            HbServerConfig & operator =( const HbServerConfig & config );

            bool isValid() const;

            virtual void setMaxUsersPerThread( quint16 max_users ) final;
            virtual quint16 maxUsersPerThread() const final;
            virtual bool isThreaded() const final;

        private:
            quint16 mMaxUsersPerThread;
        };
    }
}

using hb::com::HbServerConfig;

#endif // HBSERVERCONFIG_H
