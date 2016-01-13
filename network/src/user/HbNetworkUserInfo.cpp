// Qt
// Hb
// Local
#include <user/HbNetworkUserInfo.h>
#include <service/auth/HbAuthService.h>

using namespace hb::network;

HbNetworkUserInfo::HbNetworkUserInfo()
{
    mType = HbAuthService::AUTH_NONE;
    mAge = 0;
    mGender = GENDER_NONE;
}

HbNetworkUserInfo::HbNetworkUserInfo( const HbNetworkUserInfo & source )
{
    if( &source != this )
    {
        mId        = source.mId;
        mType      = source.mType;
        mEmail     = source.mEmail;
        mNickname  = source.mNickname;
        mFirstName = source.mFirstName;
        mLastName  = source.mLastName;
        mAge       = source.mAge;
        mGender    = source.mGender;
    }
}

HbNetworkUserInfo & HbNetworkUserInfo::operator=( const HbNetworkUserInfo & source )
{
    if( &source != this )
    {
        mId        = source.mId;
        mType      = source.mType;
        mEmail     = source.mEmail;
        mNickname  = source.mNickname;
        mFirstName = source.mFirstName;
        mLastName  = source.mLastName;
        mAge       = source.mAge;
        mGender    = source.mGender;
    }
    return ( *this );
}

const QString & HbNetworkUserInfo::id() const
{
    return mId;
}

authstgy  HbNetworkUserInfo::type() const
{
    return mType;
}

const QString & HbNetworkUserInfo::email() const
{
    return mEmail;
}

const QString & HbNetworkUserInfo::nickname() const
{
    return mNickname;
}

const QString & HbNetworkUserInfo::firstName() const
{
    return mFirstName;
}

const QString & HbNetworkUserInfo::lastName() const
{
    return mLastName;
}

quint8 HbNetworkUserInfo::age() const
{
    return mAge;
}

auto HbNetworkUserInfo::gender() const -> Gender
{
    return mGender;
}

void HbNetworkUserInfo::setId( const QString & id )
{
    if( !id.isEmpty() ) mId = id;
}

void HbNetworkUserInfo::setType( authstgy type )
{
    if( type != HbAuthService::AUTH_NONE ) mType = type;
}

void HbNetworkUserInfo::setEmail( const QString & email )
{
    if( !email.isEmpty() ) mEmail = email;
}

void HbNetworkUserInfo::setNickname( const QString & nickname )
{
    if( !nickname.isEmpty() ) mNickname = nickname;
}

void HbNetworkUserInfo::setFirstName( const QString & first_name )
{
    if( !first_name.isEmpty() ) mFirstName = first_name;
}

void HbNetworkUserInfo::setLastName ( const QString & last_name )
{
    if( !last_name.isEmpty() ) mLastName = last_name;
}

void HbNetworkUserInfo::setAge      ( quint8 age )
{
    if( age > 0 ) mAge = age;
}

void HbNetworkUserInfo::setGender   ( Gender gender )
{
    if( gender != GENDER_NONE ) mGender = gender;
}

namespace hb
{
    namespace network
    {

        QDataStream & operator <<( QDataStream & stream, const HbNetworkUserInfo & user_info )
        {
            stream << user_info.mId;
            stream << user_info.mType;
            stream << user_info.mEmail;
            stream << user_info.mNickname;
            stream << user_info.mFirstName;
            stream << user_info.mLastName;
            stream << user_info.mAge;
            stream << ( netwint ) user_info.mGender;

            return stream;
        }

        QDataStream & operator >>( QDataStream & stream, HbNetworkUserInfo & user_info )
        {
            netwint gender;
            stream >> user_info.mId;
            stream >> user_info.mType;
            stream >> user_info.mEmail;
            stream >> user_info.mNickname;
            stream >> user_info.mFirstName;
            stream >> user_info.mLastName;
            stream >> user_info.mAge;
            stream >> gender;

            user_info.mGender = ( HbNetworkUserInfo::Gender ) gender;

            return stream;
        }
    }
}


