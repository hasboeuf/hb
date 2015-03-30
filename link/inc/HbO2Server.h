/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBO2SERVER_H
#define HBO2SERVER_H

/*! \file HbO2Server.h */

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

        /*!
         * HbO2Server provides server side authentication flow.
         * Abstract class.
         */
        class HB_LINK_DECL HbO2Server : public HbO2
        {
            Q_OBJECT

        public:

            HbO2Server() = default;
            virtual ~HbO2Server() = default;

            virtual bool isValid() const override;

            /*!
             * Return config.
             * \return Config.
             */
            virtual HbO2ServerConfig & config();
            /*!
             * Return const config.
             * \return Const config.
             */
            virtual const HbO2ServerConfig & config() const;

            virtual bool link() override;

            /*!
             * Set redirect Uri.
             * Must be the same than used in HbO2Client.
             * \param redirect_uri Redirect Uri.
             */
            void setRedirectUri( const QString & redirect_uri );

            /*!
             * Set the auth code.
             * Must be the one obtained in HbO2Client.
             * \param code Auth code.
             */
            void setCode( const QString & code );

            /*!
             * Return token.
             * \return Auth token.
             */
            virtual const QString & token() const final;

            /*!
             * Return token expiration.
             * In seconds.
             * \return Token expiration.
             */
            virtual qint32 tokenExpiration() const final;

        protected:
            virtual const QHash< QString, QString > tokenRequest() const = 0;
            virtual LinkStatus tokenResponse( const QHash< QString, QString > & response ) = 0;

        private slots:
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
