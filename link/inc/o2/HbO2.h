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
#include <HbLinkServer.h>


namespace hb
{
    namespace link
    {
        class HB_LINK_DECL HbO2 : public QObject
        {
            Q_OBJECT

        public:
            HbO2();
            virtual ~HbO2() = default;

            virtual bool isValid() const;

            virtual void link();

            virtual void setClientId( const QString & client_id ) final;
            virtual void setLocalPort( quint16 local_port ) final;
            virtual void setCode( const QString & code ) final;

            virtual const QString & clientId() const final;
            virtual quint16 localPort() const final;
            virtual const QString & redirectUri() const final;
            virtual const QString & code() const final;

        protected:
            virtual void setRequestUrl( QString request_url ) final;

        public slots:
            void onParametersReceived(const QMap<QString, QString> query_parameters );

        signals:
            void openBrowser( const QUrl & url );
            void linkingFailed();
            void linkingSucceed();

        private:
            bool mLinked;

            QString mClientId;
            //QString mClientSecret;
            //QString mScope;
            QString mCode;
            QString mRedirectUri;
            quint16 mLocalPort;
            //QString mLocalhostPolicy;
            QUrl mRequestUrl;
            QUrl mTokenUrl;
            //QUrl mRefreshTokenUrl;
            //QNetworkAccessManager * mpManager;
            //O2ReplyServer * mpReplyServer;
            //O2ReplyList mTimedReplies;
            //quint16 mLocalPort;
            //GrantFlow mGrantFlow_;
            //O2AbstractStore * mpStore_;
            //QVariantMap mExtraTokens;

            HbLinkServer mReplyServer;
        };
    }
}

using hb::link::HbO2;

#endif // HBO2_H
