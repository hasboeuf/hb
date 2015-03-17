/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBO2CLIENTFACEBOOK_H
#define HBO2CLIENTFACEBOOK_H

/*! \file HbO2ClientFacebook.h */

// Qt
#include <QtCore/QObject>
#include <QtCore/QUrl>
// Local
#include <HbO2Client.h>


namespace hb
{
    namespace link
    {
        /*!
         * TODOC
         */
        class HB_LINK_DECL HbO2ClientFacebook : public HbO2Client
        {
            Q_OBJECT

        public:
            HbO2ClientFacebook() = default;
            virtual ~HbO2ClientFacebook() = default;
            HbO2ClientFacebook( const HbO2ClientFacebook & source );
            HbO2ClientFacebook & operator =( const HbO2ClientFacebook & source );

            virtual bool read( QDataStream & stream );
            virtual bool write( QDataStream & stream ) const;

        protected:
            virtual const QUrl endPoint() const;
            virtual const QHash< QString, QString > codeRequest() const;
            virtual LinkStatus codeResponse( const QHash< QString, QString > & response );
        };
    }
}

using hb::link::HbO2ClientFacebook;

#endif // HBO2CLIENTFACEBOOK_H
