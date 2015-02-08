// Qt
#include <QtCore/QJsonObject>
// Hb
#include <HbLogService.h>
// Local
#include <facebook/api/HbFacebookUser.h>
#include <HbLinkConstant.h>

using namespace hb::link;

HbFacebookUser::HbFacebookUser() :
    HbFacebookObject()
{
    mType     = OBJECT_USER;
    mVerified = false;
    mTimezone = -1;
}

void HbFacebookUser::load( const QJsonDocument & doc )
{
    HbInfo( "Loading json into facebook user: %s",
            HbLatin1( QString( doc.toJson( QJsonDocument::Indented ) ) ) );

    QJsonObject root( doc.object() );

    mId        = root.value( FB_OBJECT_ID ).toString();
    mFirstName = root.value( FB_USER_FIRST_NAME ).toString();
    mLastName  = root.value( FB_USER_LAST_NAME ).toString();
    mLink      = root.value( FB_USER_LINK ).toString();
    mEmail     = root.value( FB_USER_EMAIL ).toString();
    mGender    = root.value( FB_USER_GENDER ).toString();
    mLocale    = root.value( FB_USER_LOCALE ).toString();
    mVerified  = root.value( FB_USER_VERIFIED ).toBool();
    mTimezone  = root.value( FB_USER_TIMEZONE ).toInt();
}

const QString HbFacebookUser::toString() const
{
    return QString( "%1; %2=%3; %4=%5; %6=%7; %8=%9; %10=%11; %12=%13; %14=%15; %16=%17" )
            .arg( HbFacebookObject::toString() )
            .arg( FB_USER_EMAIL )
            .arg( mEmail )
            .arg( FB_USER_VERIFIED )
            .arg( mVerified )
            .arg( FB_USER_FIRST_NAME )
            .arg( mFirstName )
            .arg( FB_USER_LAST_NAME )
            .arg( mLastName )
            .arg( FB_USER_GENDER )
            .arg( mGender )
            .arg( FB_USER_LOCALE )
            .arg( mLocale )
            .arg( FB_USER_LINK )
            .arg( mLink )
            .arg( FB_USER_TIMEZONE )
            .arg( mTimezone );
}

const QString & HbFacebookUser::firstName() const
{
	return mFirstName;
}

const QString & HbFacebookUser::lastName() const
{
	return mLastName;
}

const QString & HbFacebookUser::link() const
{
	return mLink;
}

const QString & HbFacebookUser::email() const
{
	return mEmail;
}

const QString & HbFacebookUser::gender() const
{
	return mGender;
}

const QString & HbFacebookUser::locale() const
{
	return mLocale;
}

bool HbFacebookUser::isVerified() const
{
	return mVerified;
}

qint8 HbFacebookUser::timezone() const
{
	return mTimezone;
}

void HbFacebookUser::setFirstName( const QString & first_name )
{
	mFirstName = first_name;
}
void HbFacebookUser::setLastName ( const QString & last_name  )
{
	mLastName = last_name;
}
void HbFacebookUser::setLink     ( const QString & link       )
{
	mLink = link;
}
void HbFacebookUser::setEmail    ( const QString & email      )
{
	mEmail = email;
}
void HbFacebookUser::setGender   ( const QString & gender     )
{
	mGender = gender;
}
void HbFacebookUser::setLocale   ( const QString & locale     )
{
	mLocale = locale;
}
void HbFacebookUser::setVerified ( bool            verified   )
{
	mVerified = verified;
}
void HbFacebookUser::setTimezone ( qint8           timezone   )
{
	mTimezone = timezone;
}
