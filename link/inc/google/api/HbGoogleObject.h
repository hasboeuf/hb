/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBGOOGLEOBJECT_H
#define HBGOOGLEOBJECT_H

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
        /*!
         * HbGoogleObject represents an abstract Google object.
         */
        class HB_LINK_DECL HbGoogleObject
        {
            Q_GADGET
            Q_ENUMS_HANDLER( HbGoogleObject )
            Q_ENUMS( ObjectType )

        public:
            enum ObjectType
            {
                OBJECT_NONE = 0,
                OBJECT_USER
            };
            Q_META_ENUMS( ObjectType )

            HbGoogleObject();
            virtual ~HbGoogleObject() = default;

            /*!
             * Create object from a JSON document.
             * \todo May be a factory?
             * \param doc JSON document.
             */
            virtual void load( const QJsonDocument & doc ) = 0;

            /*!
             * Convenient method to print Google object informations.
             * \return Stringified object.
             */
            virtual const QString toString() const;

            /*!
             * Set the Google id of the object.
             * \param id Google id.
             */
            virtual void setId( const QString & id ) final;

            /*!
             * Return the Google id.
             * \return Google id.
             */
            virtual const QString & id() const final;

            /*!
             * Return the object type.
             * \return Object type.
             * \sa ObjectType
             */
            virtual ObjectType type() const final;

        protected:
            QString    mId;
            ObjectType mType;
        };
    }
}


using hb::link::HbGoogleObject;

#endif // HBGOOGLEOBJECT_H
