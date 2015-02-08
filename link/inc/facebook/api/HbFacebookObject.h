/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBFACEBOOKOBJECT_H
#define HBFACEBOOKOBJECT_H

// Qt
#include <QtCore/QString>
// Hb
#include <core/HbEnum.h>
// Local
#include <HbLink.h>

namespace hb
{
    namespace link
    {
        class HB_LINK_DECL HbFacebookObject
        {
            Q_GADGET
            Q_ENUMS_HANDLER( HbFacebookObject )
            Q_ENUMS( ObjectType )

        public:
            enum ObjectType
            {
                OBJECT_NONE = 0,
                OBJECT_USER
            };
            Q_META_ENUMS( ObjectType )

            HbFacebookObject();
            virtual ~HbFacebookObject() = default;

            virtual void load( const QJsonDocument & doc ) = 0;

            const QString toString() const;

            virtual void setId( const QString & id ) final;
            virtual const QString & id()   const final;
            virtual ObjectType      type() const final;

        protected:
            QString    mId;
            ObjectType mType;
        };
    }
}


using hb::link::HbFacebookObject;

#endif // HBFACEBOOKOBJECT_H
