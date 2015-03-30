/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBFACEBOOKUSER_H
#define HBFACEBOOKUSER_H

/*! \file HbFacebookUser.h */

// Qt
#include <QtCore/QString>
#include <QtCore/QJsonDocument>
// Local
#include <HbLink.h>
#include <facebook/api/HbFacebookObject.h>

namespace hb
{
    namespace link
    {
        /*!
         * HbFacebookUser describes a Facebook user object.
         */
        class HB_LINK_DECL HbFacebookUser : public HbFacebookObject
        {

        public:
            HbFacebookUser();
            virtual ~HbFacebookUser() = default;

            virtual void load( const QJsonDocument & doc ) override;

            virtual const QString toString() const override;

            virtual const QString & firstName()  const final;
            virtual const QString & lastName()   const final;
            virtual const QString & link()       const final;
            virtual const QString & email()      const final;
            virtual const QString & gender()     const final;
            virtual const QString & locale()     const final;
            virtual bool            isVerified() const final;
            virtual qint8           timezone()   const final;

            virtual void setFirstName( const QString & first_name ) final;
            virtual void setLastName ( const QString & last_name  ) final;
            virtual void setLink     ( const QString & link       ) final;
            virtual void setEmail    ( const QString & email      ) final;
            virtual void setGender   ( const QString & gender     ) final;
            virtual void setLocale   ( const QString & locale     ) final;
            virtual void setVerified ( bool            verified   ) final;
            virtual void setTimezone ( qint8           timezone   ) final;


        protected:
            QString mFirstName;
            QString mLastName;
            QString mLink;
            QString mEmail;
            QString mGender;
            QString mLocale;
            bool    mVerified;
            qint8   mTimezone;
        };
    }
}

using hb::link::HbFacebookUser;

#endif // HBFACEBOOKUSER_H
