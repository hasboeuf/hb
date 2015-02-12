/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBHTTPREQUESTER_H
#define HBHTTPREQUESTER_H

// Qt
#include <QtNetwork/QNetworkAccessManager>
#include <QtCore/QJsonDocument>
// Local
#include <network/HbTimeoutNetworkReplies.h>
#include <HbTools.h>

namespace hb
{
    namespace link
    {
        class HB_TOOLS_DECL HbHttpRequester : public QObject
        {
            Q_OBJECT

        public:
            HbHttpRequester();
            virtual ~HbHttpRequester() = default;

            qint64 processRequest( const QUrl & url, quint32 timeout = hb::tools::HbTimeoutNetworkReply::msDefaultTimeout );

        public slots:
            void onFinished();
            void onError( const QNetworkReply::NetworkError & error );

        signals:
            void requestFinished( quint64 request_id, const QJsonDocument & response );
            void requestError   ( quint64 request_id, const QString & error );

        private:
            QNetworkAccessManager mManager;
            HbTimeoutNetworkReplies mReplies;
        };
    }
}

using hb::link::HbHttpRequester;

#endif // HbHttpRequester_H
