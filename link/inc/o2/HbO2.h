/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBO2_H
#define HBO2_H

// Qt
#include <QtCore/QObject>
#include <QtCore/QUrl>
// Local
#include <HbLink.h>
#include <HbLinkConstant.h>
#include <HbLinkServer.h>


namespace hb
{
    namespace link
    {
        class HB_LINK_DECL HbO2 : public QObject
        {
            Q_OBJECT

        public:
            enum LinkStatus
            {
                UNLINKED = 0,
                LINKING,
                LINKED
            };

            HbO2();
            virtual ~HbO2() = default;

            virtual bool isValid() const;

            virtual void link();

            virtual void setClientId( const QString & client_id ) final;
            virtual void setLocalPort( quint16 local_port ) final;
            virtual void addScope( const QString & permission ) final;

            virtual const QString & errorString() const final;
            virtual const QString & clientId() const final;
            virtual quint16 localPort() const final;
            virtual const QString & redirectUri() const final;
            virtual const QString & code() const final;
            virtual const QString & scope() const final;


        protected:
            // Target specific.
            virtual const QUrl endPoint() const = 0;
            virtual const QHash< QString, QString > codeRequest() const = 0;
            virtual LinkStatus codeResponse( const QHash< QString, QString > & response ) = 0;

        public slots:
            void onResponseReceived( const QHash< QString, QString > response_parameters );

        signals:
            void openBrowser( const QUrl & url );
            void linkingFailed( QString error );
            void linkingSucceed();

        protected:
            QString mErrorString;
            QString mCode;

        private:
            LinkStatus mLinkStatus;
            HbLinkServer mReplyServer;

            // Code request
            QString mClientId;
            QString mScope;
            QString mRedirectUri;
            quint16 mLocalPort;
        };
    }
}

using hb::link::HbO2;

#endif // HBO2_H
