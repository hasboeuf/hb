/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBCOMCONFIG_H
#define HBCOMCONFIG_H

// Qt
#include <QtCore/QIODevice>
// Hb
#include <HbGlobal.h>
// Local
#include <HbCom.h>
#include <contract/HbComExchanges.h>

namespace hb
{
    namespace com
    {
        class HB_COM_DECL HbComConfig
        {
        public:
            HbComConfig();
            virtual ~HbComConfig() = default;
            HbComConfig(const HbComConfig & config);
            virtual HbComConfig & operator =(const HbComConfig & config);

            virtual bool isValid() const;

            virtual void setOpenMode(QIODevice::OpenMode mode) final;
            virtual QIODevice::OpenMode openMode() const final;

            virtual const HbComExchanges & exchanges() const final;
            virtual HbComExchanges & exchanges() final;



        protected:
            HbComExchanges mExchanges;

        private:
            QIODevice::OpenMode mOpenMode;

        };
    }
}

using hb::com::HbComConfig;

#endif // HBCOMCONFIG_H
