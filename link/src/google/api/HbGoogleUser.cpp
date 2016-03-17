// Qt
#include <QtCore/QJsonObject>
// Hb
#include <HbLogService.h>
// Local
#include <google/api/HbGoogleUser.h>
#include <HbLinkConstant.h>

using namespace hb::link;

HbGoogleUser::HbGoogleUser() :
    HbGoogleObject()
{
    mType     = OBJECT_USER;
    mVerified = false;
}

void HbGoogleUser::load( const QJsonDocument & doc )
{
    HbInfo( "Loading json into google user: %s",
            HbLatin1( QString( doc.toJson( QJsonDocument::Indented ) ) ) );

    QJsonObject root( doc.object() );

    mId        = root.value( GL_OBJECT_ID ).toString();
    mFirstName = root.value( GL_USER_FIRST_NAME ).toString();
    mLastName  = root.value( GL_USER_LAST_NAME ).toString();
    mLink      = root.value( GL_USER_LINK ).toString();
    mEmail     = root.value( GL_USER_EMAIL ).toString();
    mGender    = root.value( GL_USER_GENDER ).toString();
    mLocale    = root.value( GL_USER_LOCALE ).toString();
    mVerified  = root.value( GL_USER_VERIFIED ).toBool();
    mPicture   = root.value( GL_USER_PICTURE ).toString();
}

const QString HbGoogleUser::toString() const
{
    return QString( "%1; %2=%3; %4=%5; %6=%7; %8=%9; %10=%11; %12=%13; %14=%15; %16=%17" )
            .arg( HbGoogleObject::toString() )
            .arg( GL_USER_EMAIL )
            .arg( mEmail )
            .arg( GL_USER_VERIFIED )
            .arg( mVerified )
            .arg( GL_USER_FIRST_NAME )
            .arg( mFirstName )
            .arg( GL_USER_LAST_NAME )
            .arg( mLastName )
            .arg( GL_USER_GENDER )
            .arg( mGender )
            .arg( GL_USER_LOCALE )
            .arg( mLocale )
            .arg( GL_USER_LINK )
            .arg( mLink )
            .arg( GL_USER_PICTURE )
            .arg( mPicture );
}

const QString & HbGoogleUser::firstName() const
{
    return mFirstName;
}

const QString & HbGoogleUser::lastName() const
{
    return mLastName;
}

const QString & HbGoogleUser::link() const
{
    return mLink;
}

const QString & HbGoogleUser::email() const
{
    return mEmail;
}

const QString & HbGoogleUser::gender() const
{
    return mGender;
}

const QString & HbGoogleUser::locale() const
{
    return mLocale;
}

bool HbGoogleUser::isVerified() const
{
    return mVerified;
}

const QString & HbGoogleUser::picture() const
{
    return mPicture;
}

void HbGoogleUser::setFirstName( const QString & first_name )
{
    mFirstName = first_name;
}
void HbGoogleUser::setLastName ( const QString & last_name  )
{
    mLastName = last_name;
}
void HbGoogleUser::setLink     ( const QString & link       )
{
    mLink = link;
}
void HbGoogleUser::setEmail    ( const QString & email      )
{
    mEmail = email;
}
void HbGoogleUser::setGender   ( const QString & gender     )
{
    mGender = gender;
}
void HbGoogleUser::setLocale   ( const QString & locale     )
{
    mLocale = locale;
}
void HbGoogleUser::setVerified ( bool            verified   )
{
    mVerified = verified;
}
void HbGoogleUser::setPicture( const QString & picture )
{
    mPicture = picture;
}
