/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBTIMEOUTNETWORKREPLIES_H
#define HBTIMEOUTNETWORKREPLIES_H

// Qt
#include <QtCore/QObject>
#include <QtCore/QList>
// Local
#include <HbTools.h>
#include <network/HbTimeoutNetworkReply.h>

namespace hb
{
    namespace tools
    {
        class HB_TOOLS_DECL HbTimeoutNetworkReplies : public QObject
        {
            Q_OBJECT

        public:
            HbTimeoutNetworkReplies() = default;
            virtual ~HbTimeoutNetworkReplies();

            quint64 add( QNetworkReply * reply, quint32 timeout = HbTimeoutNetworkReply::msDefaultTimeout );

            void remove( QNetworkReply * reply );

            quint64 id( QNetworkReply * reply ) const;

        public slots:
            void onDestroyed();
        private:
            QHash< QNetworkReply *, HbTimeoutNetworkReply * > mReplies;
        };
    }
}

using hb::tools::HbTimeoutNetworkReplies;

#endif // HBTIMEOUTNETWORKREPLIES_H
