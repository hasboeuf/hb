/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBO2SERVER_H
#define HBO2SERVER_H

// Qt
#include <QtNetwork/QNetworkAccessManager>
// Hb
#include <network/HbTimeoutNetworkReplies.h>
// Local
#include <HbO2.h>
#include <config/HbO2ServerConfig.h>


namespace hb
{
    namespace link
    {
        class HB_LINK_DECL HbO2Server : public HbO2
        {
            Q_OBJECT

        public:

            HbO2Server() = default;
            virtual ~HbO2Server() = default;

            virtual bool isValid() const;

            virtual HbO2ServerConfig & config();
            virtual const HbO2ServerConfig & config() const;

            virtual bool link();

            void setRedirectUri( const QString & redirect_uri );
            void setCode( const QString & code );

            virtual const QString & token() const final;
            virtual qint32 tokenExpiration() const final;

        protected:
            // Target specific.
            virtual const QUrl endPoint() const = 0;
            virtual const QHash< QString, QString > tokenRequest() const = 0;
            virtual LinkStatus tokenResponse( const QHash< QString, QString > & response ) = 0;

        public slots:
            void onTokenResponseReceived();
            void onTokenResponseError( QNetworkReply::NetworkError error );

        protected:
            HbO2ServerConfig mConfig;
            QString mToken;
            qint32  mTokenExpiration;

        private:
            QNetworkAccessManager mManager;
            HbTimeoutNetworkReplies mReplies;
        };
    }
}

using hb::link::HbO2Server;

#endif // HBO2SERVER_H
