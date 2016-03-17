/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBGOOGLEUSER_H
#define HBGOOGLEUSER_H

// Qt
#include <QtCore/QString>
#include <QtCore/QJsonDocument>
// Local
#include <HbLink.h>
#include <google/api/HbGoogleObject.h>

namespace hb
{
    namespace link
    {
        /*!
         * HbGoogleUser describes a Google user object.
         */
        class HB_LINK_DECL HbGoogleUser : public HbGoogleObject
        {

        public:
            HbGoogleUser();
            virtual ~HbGoogleUser() = default;

            virtual void load( const QJsonDocument & doc ) override;

            virtual const QString toString() const override;

            virtual const QString & firstName()  const final;
            virtual const QString & lastName()   const final;
            virtual const QString & link()       const final;
            virtual const QString & email()      const final;
            virtual const QString & gender()     const final;
            virtual const QString & locale()     const final;
            virtual bool            isVerified() const final;
            virtual const QString & picture()    const final;

            virtual void setFirstName( const QString & first_name ) final;
            virtual void setLastName ( const QString & last_name  ) final;
            virtual void setLink     ( const QString & link       ) final;
            virtual void setEmail    ( const QString & email      ) final;
            virtual void setGender   ( const QString & gender     ) final;
            virtual void setLocale   ( const QString & locale     ) final;
            virtual void setVerified ( bool            verified   ) final;
            virtual void setPicture  ( const QString & picture    ) final;

        protected:
            QString mFirstName;
            QString mLastName;
            QString mLink;
            QString mEmail;
            QString mGender;
            QString mLocale;
            bool    mVerified;
            QString mPicture;
        };
    }
}

using hb::link::HbGoogleUser;

#endif // HBGOOGLEUSER_H
