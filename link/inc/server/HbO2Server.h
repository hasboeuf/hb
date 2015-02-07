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

            virtual bool link();

            virtual void setClientSecret( const QString & client_secret ) final;
            virtual const QString & clientSecret() const final;

            void setRedirectUri( const QString & redirect_uri );
            void setCode( const QString & code );

        protected:
            // Target specific.
            virtual const QUrl endPoint() const = 0;
            virtual const QHash< QString, QString > tokenRequest() const = 0;
            virtual LinkStatus tokenResponse( const QHash< QString, QString > & response ) = 0;

        public slots:
            void onTokenResponseReceived();
            void onTokenResponseError( QNetworkReply::NetworkError error );

        protected:
            QString mClientSecret;

        private:
            QNetworkAccessManager mManager;
            HbTimeoutNetworkReplies mReplies;
        };
    }
}

using hb::link::HbO2Server;

#endif // HBO2SERVER_H
