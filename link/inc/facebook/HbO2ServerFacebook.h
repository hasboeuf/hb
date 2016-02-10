/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBO2SERVERFACEBOOK_H
#define HBO2SERVERFACEBOOK_H

/*! \file HbO2ServerFacebook.h */

// Qt
// Local
#include <HbLink.h>
#include <HbO2Server.h>


namespace hb
{
    namespace link
    {
        /*!
         * HbO2ServerFacebook is the Facebook implementation of HbO2Server.
         */
        class HB_LINK_DECL HbO2ServerFacebook : public HbO2Server
        {
            Q_OBJECT

        public:
            HbO2ServerFacebook() = default;
            virtual ~HbO2ServerFacebook() = default;

            virtual void addField( const QString & field ) final;
            virtual void setFields( const QString & fields ) final;
            virtual const QString & fields() const final;

        protected:
            virtual const QUrl endPoint() const override;
            virtual const QHash< QString, QString > tokenRequest() const override;
            virtual LinkStatus tokenResponse( const QHash< QString, QString > & response ) override;   

        private:
            QString mFields;
        };
    }
}

using hb::link::HbO2ServerFacebook;

#endif // HBO2SERVERFACEBOOK_H
