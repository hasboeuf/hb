/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBFACEBOOKOBJECT_H
#define HBFACEBOOKOBJECT_H

/*! \file HbFacebookObject.h */

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
         * HbFacebookObject represents an abstract Facebook object.
         */
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

            /*!
             * Create object from a JSON document.
             * \todo May be a factory?
             * \param doc JSON document.
             */
            virtual void load( const QJsonDocument & doc ) = 0;

            /*!
             * Convenient method to print Facebook object informations.
             * \return Stringified object.
             */
            virtual const QString toString() const;

            /*!
             * Set the Facebook id of the object.
             * \param id Facebook id.
             */
            virtual void setId( const QString & id ) final;

            /*!
             * Return the Facebook id.
             * \return Facebook id.
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


using hb::link::HbFacebookObject;

#endif // HBFACEBOOKOBJECT_H
