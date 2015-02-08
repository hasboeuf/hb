/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBTIMEOUTNETWORKREPLY_H
#define HBTIMEOUTNETWORKREPLY_H

// Qt
#include <QtCore/QTimer>
#include <QtNetwork/QNetworkReply>
// Local
#include <HbTools.h>

namespace hb
{
	namespace tools
	{
        class HB_TOOLS_DECL HbTimeoutNetworkReply final : public QTimer
		{
            Q_OBJECT

		public:
            HbTimeoutNetworkReply( QNetworkReply * reply, quint32 timeout = msDefaultTimeout, QObject * parent = nullptr );
            ~HbTimeoutNetworkReply();

            quint64 id() const;

        signals:
            void error( QNetworkReply::NetworkError error );

        public slots:
            void onTimeout();

        public:
            static quint32 msDefaultTimeout;

        private:
            quint64 mId;
            QNetworkReply * mpReply;
		};
	}
}

using hb::tools::HbTimeoutNetworkReply;

#endif // HBTIMEOUTNETWORKREPLY_H