/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNETWORKUSERINFO_H
#define HBNETWORKUSERINFO_H

/*! \file HbNetworkUserInfo.h */

// Qt
#include <QtCore/QString>
// Hb
// Local
#include <HbNetwork.h>

namespace hb
{
    namespace network
    {
        /*!
         * TODOC
         */
        class HB_NETWORK_DECL HbNetworkUserInfo final
        {
            friend QDataStream & operator<<( QDataStream & stream, const HbNetworkUserInfo & header );
            friend QDataStream & operator>>( QDataStream & stream, HbNetworkUserInfo & header );

        public:

            enum Gender : netwint
            {
                GENDER_NONE = 0,
                GENDER_MALE,
                GENDER_FEMALE
            };

            HbNetworkUserInfo();
            virtual ~HbNetworkUserInfo() = default;
            HbNetworkUserInfo( const HbNetworkUserInfo & source );
            HbNetworkUserInfo & operator=( const HbNetworkUserInfo & source );

            const QString & id       () const;
            authstgy        type     () const;
            const QString & email    () const;
            const QString & nickname () const;
            const QString & firstName() const;
            const QString & lastName () const;
            quint8          age      () const;
            Gender          gender   () const;

            void setId       ( const QString & id );
            void setType     ( authstgy type );
            void setEmail    ( const QString & email );
            void setNickname ( const QString & nickname );
            void setFirstName( const QString & first_name );
            void setLastName ( const QString & last_name );
            void setAge      ( quint8 age );
            void setGender   ( Gender gender );


        private:
            QString  mId;
            authstgy mType;
            QString  mEmail;
            QString  mNickname;
            QString  mFirstName;
            QString  mLastName;
            quint8   mAge;
            Gender   mGender;

        };

        QDataStream & operator<<(QDataStream & stream, const HbNetworkUserInfo & header );
        QDataStream & operator>>(QDataStream & stream, HbNetworkUserInfo & header );
    }
}

using hb::network::HbNetworkUserInfo;

#endif // HBNETWORKUSERINFO_H
