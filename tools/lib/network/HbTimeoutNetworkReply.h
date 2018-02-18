/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBTIMEOUTNETWORKREPLY_H
#define HBTIMEOUTNETWORKREPLY_H

/*! \file HbTimeoutNetworkReply.h */

// Qt
#include <QtCore/QTimer>
#include <QtNetwork/QNetworkReply>
// Hb
#include <core/HbUid.h>
// Local
#include <HbTools.h>

namespace hb
{
    namespace tools
    {
        /*!
         * HbTimeoutNetworkReply invalidates a QNetworkReply if it times out.
         * \bug Does not work as expected as QNetworkReply::abort does not
         * cancel the reply. For now timeout feature is disable.
         */
        class HB_TOOLS_DECL HbTimeoutNetworkReply final : public QTimer, public HbUid< replyuid, CLASS_REPLIES, true >
        {
            Q_OBJECT

        public:
            HbTimeoutNetworkReply( QNetworkReply * reply, quint32 timeout = msDefaultTimeout );
            ~HbTimeoutNetworkReply();

        signals:
            void error( QNetworkReply::NetworkError error );

        public slots:
            void onTimeout();

        public:
            static quint32 msDefaultTimeout;

        private:

        };
    }
}

using hb::tools::HbTimeoutNetworkReply;

#endif // HBTIMEOUTNETWORKREPLY_H