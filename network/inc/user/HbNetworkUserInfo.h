/****************************************************************************
** Copyright (C) 2012-2015 Adrien Gavignet (hasboeuf)
** Contact: adrien.gavignet@gmail.com
**
** This file is part of the Hb module. Provided "AS IS", WITHOUT WARRANTIES
** OR CONDITIONS OF ANY KIND, either express or implied.
****************************************************************************/

#ifndef HBNETWORKUSERINFO_H
#define HBNETWORKUSERINFO_H

// Qt
#include <QtCore/QString>
// Hb
// Local
#include <HbNetwork.h>

namespace hb
{
	namespace network
	{

        class HB_NETWORK_DECL HbNetworkUserInfo final
		{
		public:

            enum Gender : quint8
            {
                GENDER_NONE = 0,
                GENDER_MALE,
                GENDER_FEMALE
            };

            HbNetworkUserInfo();
            virtual ~HbNetworkUserInfo( ) = default;
            HbNetworkUserInfo( const HbNetworkUserInfo & source );
            HbNetworkUserInfo & operator=( const HbNetworkUserInfo & source );

            const QString & uuid     () const;
            const authstgy  type     () const;
            const QString & email    () const;
            const QString & nickname () const;
            const QString & firstName() const;
            const QString & lastName () const;
            quint8          age      () const;
            Gender          gender   () const;

            void setUuid     ( const QString & uuid );
            void setType     ( authstgy type );
            void setEmail    ( const QString & email );
            void setNickname ( const QString & nickname );
            void setFirstName( const QString & first_name );
            void setLastName ( const QString & last_name );
            void setAge      ( quint8 age );
            void setGender   ( Gender gender );


        private:
            QString  mUuid;
            authstgy mType;
            QString  mEmail;
            QString  mNickname;
            QString  mFirstName;
            QString  mLastName;
            quint8   mAge;
            Gender   mGender;

		};
	}
}

using hb::network::HbNetworkUserInfo;

#endif // HBNETWORKUSERINFO_H
