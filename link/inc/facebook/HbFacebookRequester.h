/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBFACEBOOKREQUESTER_H
#define HBFACEBOOKREQUESTER_H

// Qt
#include <QtCore/QObject>
#include <QtCore/QString>
// Local
#include <HbLink.h>
#include <HbLinkRequester.h>
#include <facebook/api/HbFacebookObject.h>

namespace hb
{
    namespace link
    {
        class HbO2ServerFacebook;
        class HbFacebookUser;

        class HB_LINK_DECL HbFacebookRequester : public HbLinkRequester
        {
            Q_OBJECT

            // TODO hide HbLinkRequester signals.
        public:
            HbFacebookRequester();
            virtual ~HbFacebookRequester() = default;

            bool requestUser( HbO2ServerFacebook * auth );

        private slots:
            // From HbLinkRequester
            void onRequestFinished( quint64 request_id, const QJsonDocument & doc );
            void onRequestError   ( quint64 request_id, const QString & error );

        signals:
            void requestCompleted( HbFacebookObject * object );

        private:
            QHash< quint64, HbFacebookObject::ObjectType > mRequestTypes;

        };
    }
}



using hb::link::HbFacebookObject;

#endif // HBFACEBOOKREQUESTER_H