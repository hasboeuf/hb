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
         * HbO2Client provides client side authentication flow.
         * Abstract class.
         */
        class HB_LINK_DECL HbO2Client : public HbO2
        {
            Q_OBJECT

        public:
            HbO2Client() = default;
            virtual ~HbO2Client() = default;

            virtual bool isValid() const override;

            virtual bool link() override;

            /*!
             * Return config.
             * \return Config.
             */
            virtual HbO2ClientConfig & config();
            /*!
             * Return const config.
             * \return Const config.
             */
            virtual const HbO2ClientConfig & config() const;

        protected:
            virtual const QHash< QString, QString > codeRequest() const = 0;
            virtual LinkStatus codeResponse( const QHash< QString, QString > & response ) = 0;

        public slots:
            /*!
             * Fired when auth code is received.
             * \param response_parameters Response parameters.
             */
            void onCodeResponseReceived( const QHash< QString, QString > response_parameters );

        signals:
            /*!
             * Triggered during linking phase when user should give its approval on a web page.
             * Open default web browser.
             * \param url URL to open.
             */
            void openBrowser( const QUrl & url );

            /*!
             * Triggered when linking phase is done.
             * User can close its browser.
             */
            void closeBrowser();

        protected:
            HbO2ClientConfig mConfig;

        private:
            HbLinkLocalServer mReplyServer;

        };
    }
}

using hb::link::HbO2Client;

#endif // HBO2CLIENT_H
