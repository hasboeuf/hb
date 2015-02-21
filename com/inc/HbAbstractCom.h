/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HbAbstractCom_H
#define HbAbstractCom_H

// Qt
#include <QtNetwork/QAbstractSocket>
// Hb
#include <HbGlobal.h>
// Local
#include <HbCom.h>
#include <contract/HbComContract.h>
#include <config/HbComConfig.h>

namespace hb
{
    namespace com
    {

        class IHbComListener;

        class HB_COM_DECL HbAbstractCom : public QObject
        {
            Q_OBJECT
            Q_DISABLE_COPY( HbAbstractCom )

        public:

            virtual bool join() = 0;
            virtual bool leave() = 0;
            virtual bool isReady() const = 0;
            virtual HbComProtocol::ComType type() const = 0;

            virtual bool send( ShConstHbComContract contract ) = 0; // TODO refresh

            virtual const HbComConfig & configuration() const; // SUB

        protected:
            HbAbstractCom( QObject * parent = nullptr );
            virtual ~HbAbstractCom() = default;

        private:
            HbComConfig mConfig; // SUB
        };
    }
}

#endif // HbAbstractCom_H
