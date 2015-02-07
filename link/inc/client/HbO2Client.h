/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBO2CLIENT_H
#define HBO2CLIENT_H

// Qt
#include <QtCore/QObject>
#include <QtCore/QUrl>
// Local
#include <HbO2.h>
#include <client/HbLinkLocalServer.h>

namespace hb
{
    namespace link
    {
        class HB_LINK_DECL HbO2Client : public HbO2
        {
            Q_OBJECT

        public:
            HbO2Client();
            virtual ~HbO2Client() = default;

            virtual bool isValid() const;

            virtual bool link();

            virtual void setLocalPort( quint16 local_port ) final;
            virtual quint16 localPort() const final;

            virtual void addScope( const QString & permission ) final;
            virtual const QString & scope() const final;


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
            QString mScope;
            quint16 mLocalPort;

        private:
            HbLinkLocalServer mReplyServer;

        };
    }
}

using hb::link::HbO2Client;

#endif // HBO2CLIENT_H
