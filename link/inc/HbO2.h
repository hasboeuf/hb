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

            friend QDataStream & operator<<( QDataStream & stream, const HbO2 & o2 );
            friend QDataStream & operator>>( QDataStream & stream, HbO2 & o2 );

        public:
            enum LinkStatus : quint8
            {
                UNLINKED = 0,
                LINKING,
                LINKED
            };

            static QHash< QString, QString > getUrlItems( const QString & content );

            HbO2();
            virtual ~HbO2() = default;
            HbO2( const HbO2 & source );
            HbO2 & operator=( const HbO2 & source );


            virtual bool isValid() const;

            virtual bool link();

            virtual const QString & errorString() const final;
            virtual LinkStatus      linkStatus() const final;

            virtual void setClientId( const QString & client_id ) final;
            virtual const QString & clientId() const final;
            virtual const QString & redirectUri() const final;
            virtual const QString & code() const final;

            virtual bool read( QDataStream & stream );
            virtual bool write( QDataStream & stream ) const;

        protected:
            // Target specific.
            virtual const QUrl endPoint() const = 0;

        signals:
            void linkFailed( QString error );
            void linkSucceed();

        protected:
            LinkStatus mLinkStatus;
            QString mErrorString;

            QString mCode;

            QString mRedirectUri;
            QString mClientId;

        };

        HB_LINK_DECL QDataStream & operator<<( QDataStream & stream, const HbO2 & o2 );
        HB_LINK_DECL QDataStream & operator>>( QDataStream & stream, HbO2 & o2 );
    }
}

using hb::link::HbO2;

#endif // HBO2_H
