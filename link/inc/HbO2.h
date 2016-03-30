/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBO2_H
#define HBO2_H

/*! \file HbO2.h */

// Qt
#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtCore/QHash>
#include <QtCore/QDataStream>
// Hb
#include <HbGlobal.h>
// Local
#include <HbLink.h>
#include <HbLinkConstant.h>

namespace hb
{
    namespace link
    {

        /*!
         * HbO2 is the base class used by both client and server side.
         * Used during all the OAuth authentication flow.
         * Server side: master application that federates many client.
         * Client side: light application that connects to the server.
         */
        class HB_LINK_DECL HbO2 : public QObject
        {
            Q_OBJECT

        public:
            enum LinkStatus : quint8
            {
                UNLINKED = 0,
                LINKING,
                LINKED
            };

            /*!
             * Retrieve URL data.
             * \param content Enriched URL.
             * \return URL data, key: parameter name, value: associated value.
             */
            static QHash< QString, QString > getUrlItems( const QString & content );

            HbO2();
            virtual ~HbO2() = default;

            /*!
             * Check if link could be done.
             * \return True if valid, false else.
             */
            virtual bool isValid() const;

            /*!
             * Process to the OAuth link phase.
             * \return True on success, false else.
             */
            virtual bool link() = 0;

            /*!
             * Return the last occured error.
             * \return Error string.
             */
            virtual const QString & errorString() const final;

            /*!
             * Return the current link status.
             * \return Link status.
             */
            virtual LinkStatus linkStatus() const final;

            /*!
             * Return the redirect Uri.
             * \return Redirect Uri.
             */
            virtual const QString & redirectUri() const final;

            /*!
             * Return OAuth code.
             * \return Authentication code.
             */
            virtual const QString & code() const final;

        protected:
            virtual const QUrl endPoint() const = 0; //!< Target specific.

        signals:

            /*!
             * Triggered when the link phase failed.
             * \param error Link error.
             */
            void linkFailed( QString error );
            /*!
             * Triggered when the link phase succeeded.
             */
            void linkSucceed();

        protected:
            LinkStatus mLinkStatus;
            QString    mErrorString;
            QString    mCode;
            QString    mRedirectUri;
        };
    }
}

using hb::link::HbO2;

#endif // HBO2_H
