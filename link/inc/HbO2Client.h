/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBO2CLIENT_H
#define HBO2CLIENT_H

/*! \file HbO2Client.h */

// Qt
#include <QtCore/QObject>
#include <QtCore/QUrl>
// Local
#include <HbO2.h>
#include <config/HbO2ClientConfig.h>
#include <HbLinkLocalServer.h>

namespace hb
{
    namespace link
    {

        /*!
         * TODOC
         */
        class HB_LINK_DECL HbO2Client : public HbO2
        {
            Q_OBJECT

        public:
            HbO2Client() = default;
            virtual ~HbO2Client() = default;
            HbO2Client( const HbO2Client & source );
            HbO2Client & operator=( const HbO2Client & source );

            virtual bool isValid() const;

            virtual bool link();

            virtual bool read( QDataStream & stream );
            virtual bool write( QDataStream & stream ) const;

            virtual HbO2ClientConfig & config();
            virtual const HbO2ClientConfig & config() const;

        protected:
            // Target specific.
            virtual const QUrl endPoint() const = 0;
            virtual const QHash< QString, QString > codeRequest() const = 0;
            virtual LinkStatus codeResponse( const QHash< QString, QString > & response ) = 0;

        public slots:
            void onCodeResponseReceived( const QHash< QString, QString > response_parameters );

        signals:
            void openBrowser( const QUrl & url );

        protected:
            HbO2ClientConfig mConfig;

        private:
            HbLinkLocalServer mReplyServer;

        };
    }
}

#endif // HBO2CLIENT_H
