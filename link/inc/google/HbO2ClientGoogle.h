/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBO2CLIENTGOOGLE_H
#define HBO2CLIENTGOOGLE_H

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
         * HbO2ClientGoogle is the Google implementation of HbO2Client.
         */
        class HB_LINK_DECL HbO2ClientGoogle : public HbO2Client
        {
            Q_OBJECT

        public:
            HbO2ClientGoogle();
            virtual ~HbO2ClientGoogle() = default;
            HbO2ClientGoogle( const HbO2ClientGoogle & source );
            HbO2ClientGoogle & operator =( const HbO2ClientGoogle & source );

            virtual bool read( QDataStream & stream ) override;
            virtual bool write( QDataStream & stream ) const override;

        protected:
            virtual const QUrl endPoint() const override;
            virtual const QHash< QString, QString > codeRequest() const override;
            virtual LinkStatus codeResponse( const QHash< QString, QString > & response ) override;
        };
    }
}

using hb::link::HbO2ClientGoogle;

#endif // HBO2CLIENTGOOGLE_H
