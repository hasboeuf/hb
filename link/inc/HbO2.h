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
#include <QtCore/QHash>
// Hb
#include <HbGlobal.h>
// Local
#include <HbLink.h>
#include <HbLinkConstant.h>

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

            virtual bool link();

            virtual const QString & errorString() const final;

            virtual void setClientId( const QString & client_id ) final;
            virtual const QString & clientId() const final;
            virtual const QString & redirectUri() const final;
            virtual const QString & code() const final;

        protected:
            // Target specific.
            virtual const QUrl endPoint() const = 0;

        signals:
            void linkingFailed( QString error );
            void linkingSucceed();

        protected:
            LinkStatus mLinkStatus;
            QString mErrorString;

            QString mCode;

            QString mRedirectUri;
            QString mClientId;

        };
    }
}

#endif // HBO2_H
